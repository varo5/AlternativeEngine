#pragma once
#include "aePrerequisitesUtil.h"
#include "aeRandomNumberGenerator.h"

namespace aeEngineSDK
{
	class AE_UTILITY_EXPORT aeZiggurat
	{
	public:
		
		aeZiggurat();
		aeZiggurat(const aeZiggurat& Z);
		~aeZiggurat();

		void Seed(uint32);

		/**********************************************************************************************//**
		 * @fn	double aeZiggurat::DRand();
		 *
		 * @brief	Gets a random .
		 *
		 * @return	A double.
		 **************************************************************************************************/

		double DRand();

		/**********************************************************************************************//**
		 * @fn	double aeZiggurat::UDRand();
		 *
		 * @brief	Gets the random.
		 *
		 * @return	A double.
		 **************************************************************************************************/

		double UDRand();
	private:

		/**********************************************************************************************//**
		 * @fn	void aeZiggurat::CreateTables();
		 *
		 * @brief	Creates the tables.
		 **************************************************************************************************/

		void CreateTables();

		static const uint32 ZIGGURAT_TABLE_SIZE;
		static const double ZIGGURAT_R;
		static const double ZIGGURAT_INV_R;
		static const double TWO_TO_POWER_31;
		static const double SECTION_AREA;		

		aeRNG m_xRNG;	///< The random number generator

		Vector<uint32> ki; ///< The ki
		Vector<double> wi; ///< The wi
		Vector<double> fi; ///< The fi
	};
}
