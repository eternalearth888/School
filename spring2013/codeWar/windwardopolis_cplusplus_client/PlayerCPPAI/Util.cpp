#include "stdafx.h"
#include "Util.h"

namespace PlayerCPPAI
{
	namespace api
	{
		Company^ findCompany(List<Company^> ^companies, String ^name)
		{
			for each(Company^ cpy in companies)
				if (cpy->Name->Equals(name))
					return cpy;
			return nullptr;
		}

		Passenger^ findPassenger(List<Passenger^> ^passengers, String ^name)
		{
			for each (Passenger^ psngr in passengers)
				if (psngr->Name->Equals(name))
					return psngr;
			return nullptr;
		}

		Player^ findPlayer(List<Player^>^ players, String^ guid)
		{
			for each(Player^ plyr in players)
				if (plyr->Guid->Equals(guid))
					return plyr;
			return nullptr;
		}
	}
}