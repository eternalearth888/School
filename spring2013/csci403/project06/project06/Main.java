/*
 * MARIA DESLIS
 * BAKOS - CSCI403
 * SPRING 2013
 * PROJECT06
 *
 */

import java.sql.*;
import javax.sql.*;
import java.sql.PreparedStatement;
import java.util.*;

public class Main {

  public void welcome() {
    System.out.println("Welcome to the Albums Database! Please choose an option: ");
    System.out.println();
    System.out.println("1. Display all albums");
    System.out.println("2. Insert a new album");
    System.out.println("3. Update an existing album");
    System.out.println("4. Delete an album");
    System.out.print("> ");
  }

  public void selection(int choice) {
    Main app = new Main();
    switch (choice) {
      case 1:
        app.run();
        break;
      case 2:
        app.insertRecord();
        break;
      case 3:
        app.updateRecord();
        break;
      case 4:
        app.deleteRecord();
        break;
      default:
        System.out.println("Error! Not a valid choice. Goodbye!");
        break;
    }
  }

  public static void main(String[] args) {
    Main app = new Main();
    app.welcome();

    Scanner scanner = new Scanner(System.in);
    int choice = scanner.nextInt();

    app.selection(choice);
  }

  private void run() {
    System.out.println("Rolling Stone's Supposed Top 100 Albums of All Time");
    try {
      Class.forName("org.sqlite.JDBC");
      Connection conn = DriverManager.getConnection("jdbc:sqlite:albums.sqlite3.db");
      Statement stmt = conn.createStatement();
      ResultSet results = stmt.executeQuery("SELECT * FROM albums;");
      while (results.next()) {
        System.out.println( results.getInt("rank") + " " + results.getString("title") + " (" + results.getInt("year") + ")");
      }
      conn.close();
    } catch (ClassNotFoundException e) {
      System.out.println("Could not load SQLite JDBC Driver.");
      System.out.println(e.getMessage());
    } catch (SQLException e) {
      System.out.println("SQL Error.");
      System.out.println(e.getMessage());
    }
  }

  public void insertRecord() {
    System.out.println("New Album: ");

    String query = "INSERT INTO albums (title, year, rank) VALUES(?,?,?);";

    Scanner scanner = new Scanner(System.in);

    try {
      //  Connect to the database
      Class.forName("org.sqlite.JDBC");
      Connection conn = DriverManager.getConnection("jdbc:sqlite:albums.sqlite3.db");
      //  Set all the preparedStatement parameters
      PreparedStatement stmt = conn.prepareStatement(query);

      System.out.print("Title: ");
      String newTitle = scanner.nextLine();
      stmt.setString(1, newTitle); // album title

      System.out.print("Year: ");
      int newYear = scanner.nextInt();
      stmt.setInt(2, newYear);    // album year

      System.out.print("Rank: ");
      int newRank = scanner.nextInt();
      stmt.setInt(3, newRank);    // album rank

      stmt.executeUpdate();

      System.out.println("Album Saved");

      stmt.close();
    } catch (ClassNotFoundException e) {
      System.out.println("Could not load SQLite JDBC Driver.");
      System.out.println(e.getMessage());
    } catch (SQLException e) {
      System.out.println("SQL Error.");
      System.out.println(e.getMessage());
    }
  }

  public void updateRecord() {
    System.out.println("Update Album ");

    Scanner scanner = new Scanner(System.in);

    System.out.print("Choose Album ID/Record: ");
    int albumId = scanner.nextInt();
    scanner.nextLine();
 
    try {
      //  Connect to the database
      Class.forName("org.sqlite.JDBC");
      Connection conn = DriverManager.getConnection("jdbc:sqlite:albums.sqlite3.db");

      //  Print out the original record
      Statement original = conn.createStatement();
      ResultSet results = original.executeQuery("SELECT * FROM albums WHERE id=" + albumId + ";");
      while (results.next()) {
        System.out.println( results.getInt("rank") + " " + results.getString("title") + " (" + results.getInt("year") + ")");
      }

      //  Set all the preparedStatement parameters
      String query = "UPDATE albums SET title = ?,year = ?,rank = ? WHERE id =" + albumId + ";";
      PreparedStatement stmt = conn.prepareStatement(query);

      System.out.print("Title: ");
      String newTitle = scanner.nextLine();
      stmt.setString(1, newTitle); // album title

      System.out.print("Year: ");
      int newYear = scanner.nextInt();
      stmt.setInt(2, newYear);    // album year

      System.out.print("Rank: ");
      int newRank = scanner.nextInt();
      stmt.setInt(3, newRank);    // album rank

      stmt.executeUpdate();

      System.out.println("Album Updated");

      stmt.close();
    } catch (ClassNotFoundException e) {
      System.out.println("Could not load SQLite JDBC Driver.");
      System.out.println(e.getMessage());
    } catch (SQLException e) {
      System.out.println("SQL Error.");
      System.out.println(e.getMessage());
    }
  }

  public void deleteRecord() {
    System.out.println("Delete Album ");

    Scanner scanner = new Scanner(System.in);

    System.out.print("Choose Album ID/Record: ");
    int albumId = scanner.nextInt();
    scanner.nextLine();

    try {
      //  Connect to the database
      Class.forName("org.sqlite.JDBC");
      Connection conn = DriverManager.getConnection("jdbc:sqlite:albums.sqlite3.db");

      //  Print out the original record
      Statement original = conn.createStatement();
      ResultSet results = original.executeQuery("SELECT * FROM albums WHERE id=" + albumId + ";");
      while (results.next()) {
        System.out.println( results.getInt("rank") + " " + results.getString("title") + " (" + results.getInt("year") + ")");
      }

      //  Set all the preparedStatement parameters
      String query = "DELETE FROM albums WHERE id = " + albumId + ";";
      PreparedStatement stmt = conn.prepareStatement(query);

      stmt.executeUpdate();

      System.out.println("Album Deleted");

      stmt.close();
    } catch (ClassNotFoundException e) {
      System.out.println("Could not load SQLite JDBC Driver.");
      System.out.println(e.getMessage());
    } catch (SQLException e) {
      System.out.println("SQL Error.");
      System.out.println(e.getMessage());
    }
  }
}
