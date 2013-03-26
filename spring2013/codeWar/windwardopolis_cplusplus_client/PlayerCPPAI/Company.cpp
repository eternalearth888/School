#include "stdafx.h"
#include "Company.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Xml;
namespace PlayerCPPAI
{
	namespace api
	{

		Company::Company(XmlElement ^elemCompany)
		{
			Name = elemCompany->GetAttribute("name");
			BusStop = Point(Convert::ToInt32(elemCompany->GetAttribute("bus-stop-x")), Convert::ToInt32(elemCompany->GetAttribute("bus-stop-y")));
			Passengers = gcnew List<Passenger^>();
		}

		List<Company^> ^Company::FromXml(XmlElement ^elemCompanies)
		{
			List<Company^> ^companies = gcnew List<Company^>();
			for each (XmlElement ^elemCmpyOn in elemCompanies->GetElementsByTagName("company"))
				companies->Add(gcnew Company(elemCmpyOn));
			return companies;
		}

		String ^Company::ToString()
		{
			return String::Format("{0}; {1}", Name, BusStop);
		}
	}
}
