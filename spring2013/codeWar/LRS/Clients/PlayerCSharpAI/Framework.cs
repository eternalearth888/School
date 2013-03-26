// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Threading;
using System.Xml.Linq;
using PlayerCSharpAI.AI;
using PlayerCSharpAI.api;

namespace PlayerCSharpAI
{
	public class Framework : IPlayerCallback
	{
		private TcpClient tcpClient;
		private readonly MyPlayerBrain brain;
		private readonly string ipAddress = "127.0.0.1";

		/// <summary>
		/// Run the A.I. player. All parameters are optional.
		/// </summary>
		/// <param name="args">I.P. address of server, name, password</param>
		public static void Main(string[] args)
		{
			Framework framework = new Framework(args);
			framework.Run();
		}

		private Framework(IList<string> args)
		{
			brain = new MyPlayerBrain(args.Count >= 2 ? args[1] : null, args.Count >= 3 ? args[2] : null);
			if (args.Count >= 1)
				ipAddress = args[0];
			Console.Out.WriteLine(string.Format("Connecting to server {0} for user: {1}, password: {2}", ipAddress, brain.Name, brain.Password));
		}

		private void Run()
		{
			Console.Out.WriteLine("starting...");

			tcpClient = new TcpClient();
			tcpClient.Start(this, ipAddress);
			ConnectToServer();

			// It's all messages to us now.
			Console.Out.WriteLine("enter \"exit\" to exit program");
			while (true)
			{
				string line = Console.ReadLine();
				if (line == "exit")
					break;
			}
		}

		public void StatusMessage(string message)
		{
			Console.Out.WriteLine(message);
		}

		public void IncomingMessage(string message)
		{
			try
			{
				DateTime startTime = DateTime.Now;
				// get the xml - we assume we always get a valid message from the server.
				XDocument xml = XDocument.Parse(message);

				switch (xml.Root.Name.LocalName)
				{
					case "start-position":
						List<Player> players = Player.FromXML(xml.Root.Element("players"));
						string guid = xml.Root.Element("players").Attribute("your-guid").Value;
						BoardLocation start = brain.Setup(new GameMap(xml.Root.Element("map")),
						                                  players.Find(pl => pl.Guid == guid), players,
						                                  GetPoints(xml.Root.Element("points")),
						                                  xml.Root.Attribute("game-start").Value.ToLower() == "true");

						Console.Out.WriteLine(string.Format("Starting robot at: {0}", start));
						XDocument doc = new XDocument(new XElement("start-position", start.Attributes));
						tcpClient.SendMessage(doc.ToString());
						break;
					case "turn":
						int turnOn = int.Parse(xml.Root.Attribute("turn").Value);
						Trace.WriteLine(string.Format("turn {0} request starting", turnOn));
						// not used in this code, but you may wish to.
						bool repairSitesOn = bool.Parse(xml.Root.Attribute("repair-on").Value);

						List<Player> allPlayers = Player.FromXML(xml.Root.Element("players"));
						string myGuid = xml.Root.Element("players").Attribute("your-guid").Value;
						PlayerTurn turn = brain.Turn(new GameMap(xml.Root.Element("map")),
						                             allPlayers.Find(pl => pl.Guid == myGuid), allPlayers,
						                             Card.FromXML(xml.Root.Element("cards")));

						Console.Out.WriteLine(string.Format("Turn: {0} - {1}", turnOn, turn));
						XDocument docTurn = new XDocument(turn.XML);
						docTurn.Root.Add(new XAttribute("turn", turnOn));
						tcpClient.SendMessage(docTurn.ToString());
						break;
					default:
						Trace.WriteLine(string.Format("ERROR: bad message (XML) from server - root node {0}", xml.Root.Name.LocalName));
						break;
				}

				TimeSpan turnTime = DateTime.Now.Subtract(startTime);
				if (turnTime.TotalMilliseconds > 800)
					Console.Out.WriteLine("WARNING - turn took {0} seconds", turnTime.TotalMilliseconds / 1000);
			}
			catch (Exception ex)
			{
				Console.Out.WriteLine(string.Format("Error on incoming message. Exception: {0}", ex));
				Trace.WriteLine(string.Format("Error on incoming message. Exception: {0}", ex));
			}
		}

		private static List<Point> GetPoints(XElement element)
		{
			return element.Elements("position").Select(elemOn => new Point(int.Parse(elemOn.Attribute("x").Value), int.Parse(elemOn.Attribute("y").Value))).ToList();
		}

		public void ConnectionLost(Exception ex)
		{

			Console.Out.WriteLine("Lost our connection! Exception: " + ex.Message);

			int delay = 500;
			while (true)
				try
				{
					if (tcpClient != null)
						tcpClient.Close();
					tcpClient = new TcpClient();
					tcpClient.Start(this, ipAddress);

					ConnectToServer();
					Console.Out.WriteLine("Re-connected");
					return;
				}
				catch (Exception e)
				{
					Console.Out.WriteLine("Re-connection fails! Exception: " + e.Message);
					Thread.Sleep(delay);
					delay += 500;
				}
		}

		private void ConnectToServer()
		{
			XDocument doc = new XDocument();
			XElement root = new XElement("join", new XAttribute("password", brain.Password), new XAttribute("name", brain.Name));
			byte[] data = brain.Avatar;
			if (data != null)
				root.Add(new XElement("avatar", Convert.ToBase64String(data)));
			doc.Add(root);
			tcpClient.SendMessage(doc.ToString());
		}
	}
}
