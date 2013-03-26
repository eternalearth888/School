#pragma once


using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Xml;

namespace PlayerCPPAI
{
	namespace api
	{
		ref class Passenger;

		public ref class Company
		{
		private:
			Company(XmlElement ^elemCompany);

		public:
			// The name of the company.
			property String ^Name;

			// The tile with the company's bus stop.
			property Point BusStop;

			// The name of the passengers waiting at this company's bus stop for a ride.
			property Collections::Generic::IList<Passenger^> ^Passengers;

			static List<Company^> ^FromXml(XmlElement ^elemCompanies);

			virtual String ^ToString() override;
		};
	}
}
