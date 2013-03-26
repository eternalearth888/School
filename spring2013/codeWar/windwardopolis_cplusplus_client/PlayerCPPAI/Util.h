#pragma once
#include "stdafx.h"
#include "Company.h"
#include "Passenger.h"
#include "Player.h"

namespace PlayerCPPAI
{
	namespace api
	{
		ref class Company;
		ref class Passenger;
		ref class Player;

		Company^ findCompany(List<Company^> ^companies, String ^name);

		Passenger^ findPassenger(List<Passenger^> ^passengers, String ^name);

		Player^ findPlayer(List<Player^>^ players, String^ guid);
	}
}