#include "$CurrentDir:\\mpmissions\\bulot2.chernarusplus\\customs\\customZombies.c"
ref customZombies m_ZombieEvents;

void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 1);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	weather.GetRain().SetLimits( 0, 0.1 );

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year;
	int month;
	int day;
	int hour;
	int minute;

	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if (((month <= 9) && (day < 20)) || ((month >= 10) && (day > 20)))
    {
        month = 9;
        day = 20;

		GetGame().GetWorld().SetDate(year, month, day, hour, minute);
	}

	//-----------------------X-mas
	array<vector> treePositions = { "6560.29 0 2462.12",
									"1652.66 0 14230.71",
									"3801.06 0 8847.76",
									"9442.32 0 8829.03",
									"7903.16 0 12576.52",
									"11617.75 0 14663.98",
									"12830.08 0 10115.18",
									"11221.94 0 12225.89",
									"3471.93 0 12988.33",
									"13933.42 0 13228.44",
									"12022.64 0 9082.89",
									"10468.54 0 2373.16",
									"2725.48 0 5288.75",
	};


	Object treeEntity;
	for ( int i=0; i < treePositions.Count(); i++ )
	{
		vector treePos = treePositions[i];
		float posY = GetGame().SurfaceY(treePos[0], treePos[2]);
		treeEntity = GetGame().CreateObject("ChristmasTree", Vector( treePos[0], posY, treePos[2]), false);

	}
	
	m_ZombieEvents = new customZombies;
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
/*
		player.RemoveAllItems();

		EntityAI item = player.GetInventory().CreateInInventory(topsMissionArray.GetRandomElement());
		EntityAI item2 = player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		EntityAI item3 = player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
*/
		EntityAI itemTop;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemTop = player.FindAttachmentBySlotName("Body");

		if ( itemTop )
		{
			itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
			if ( Class.CastTo(itemBs, itemEnt ) )
				itemBs.SetQuantity(4);

			SetRandomHealth(itemEnt);


			itemEnt = itemTop.GetInventory().CreateInInventory("RoadFlare");
			SetRandomHealth(itemEnt);

			itemEnt = itemTop.GetInventory().CreateInInventory("StoneKnife");
			SetRandomHealth(itemEnt);
		}


		//itemEnt = player.GetHumanInventory().CreateInHands("FNX45");
		//player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd",);
		//player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd",);
		//player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd",);
		itemEnt = player.GetHumanInventory().CreateInHands("Machete");
		

		rand = Math.RandomFloatInclusive(0.0, 1.0);
		if ( rand < 0.25 )
			itemEnt = player.GetInventory().CreateInInventory("SodaCan_Cola");
		else if ( rand > 0.75 )
			itemEnt = player.GetInventory().CreateInInventory("SodaCan_Spite");
		else
			itemEnt = player.GetInventory().CreateInInventory("SodaCan_Pipsi");

		SetRandomHealth(itemEnt);

		rand = Math.RandomFloatInclusive(0.0, 1.0);
		if ( rand < 0.35 )
			itemEnt = player.GetInventory().CreateInInventory("Apple");
		else if ( rand > 0.65 )
			itemEnt = player.GetInventory().CreateInInventory("Pear");
		else
			itemEnt = player.GetInventory().CreateInInventory("Plum");

		SetRandomHealth(itemEnt);
		
		GetGame().ChatPlayer(5,player.GetIdentity().GetName() + " just spawned");		
	}
	
	override void OnUpdate(float timeslice) 
	{
		super.OnUpdate( timeslice );
		
		static int tick = 0;
		static int tick2 = 0;
		static int tick3 = 0;
		static int tick4 = 0;
		int currentTime = GetGame().GetTime() * 0.001;
		
		ref array<Man> players = new array<Man>;
		
		if(currentTime >= tick + 10)
		{
			
			GetGame().GetPlayers(players);
			
			//GetGame().ChatPlayer(5,"Players on the server: " + players.Count().ToString());
			Print("[bulot]10sec tick");
			m_ZombieEvents.spawnZombies();
			m_ZombieEvents.spawnAnimals();
			m_ZombieEvents.spawnCars();
			
			for ( int iTemp = 0; iTemp < players.Count(); ++iTemp )
			{
				Man playerTemp = players.Get(iTemp);
				vector posTemp = playerTemp.GetPosition();
				float posXTemp = posTemp[0];
				float posZTemp = posTemp[2];
				string surfaceType;
				GetGame().SurfaceGetType(posXTemp,posZTemp,surfaceType);
				Print("[bulot]Surface under "+ playerTemp.GetIdentity().GetName() + " : " + surfaceType);
				Print("[bulot]Position of "+ playerTemp.GetIdentity().GetName() + " : " + posTemp.ToString());
				Print("[bulot]Info of "+ playerTemp.GetIdentity().GetName() + " : " + playerTemp.GetIdentity().GetPlainId()+" - "+ playerTemp.GetIdentity().ToString());
				
				if(playerTemp.GetIdentity().GetPlainId() == "76561198180297279")
				{

				}
				else
				{
					
				}
				
				
			}
			Print("[bulot]Players count : "+players.Count().ToString());
			
			tick = currentTime;
		}
		
		if(currentTime >= tick2 + 20)
		{
			GetGame().GetPlayers(players);
			for ( int i = 0; i < players.Count(); ++i )
			{
				Man player = players.Get(i);
				
				//array<Object> allItems = GetAllItemsAroundPos(player.GetPosition(),500);
				//GetGame().ChatPlayer(5,"Items around player" + i + " : " + allItems.Count().ToString());
				
				ref array<Object> nearestBuildings = new array<Object>;
				
				GetGame().GetObjectsAtPosition(player.GetPosition(),100, nearestBuildings, NULL);
				
				for (int nearestBuildings_i = 0; nearestBuildings_i < nearestBuildings.Count(); nearestBuildings_i++) 
				{
					if (nearestBuildings[nearestBuildings_i].IsKindOf("HouseNoDestruct")) 
					{
						array<Object> itemsAroundPos = GetAllItemsAroundPos(nearestBuildings[nearestBuildings_i].GetPosition(),5);
						//GetGame().ChatPlayer(5,"Items around "+ nearestBuildings[nearestBuildings_i].GetType() + " : "+itemsAroundPos.Count().ToString());
						if(itemsAroundPos.Count() < 5)
						{
							
							Object itemObject;
							string itemObjectClass;
							string itemObjectDisplayName;
							switch(Math.RandomIntInclusive(0,8))
							{
								case 0:
									itemObjectClass = lootOther.GetRandomElement();
									break;
								case 1:
									itemObjectClass = lootMag.GetRandomElement();
									break;
								case 2:
									itemObjectClass = lootAmmo.GetRandomElement();
									break;
								case 3:
									itemObjectClass = lootWeapon.GetRandomElement();
									break;
								case 4:
									itemObjectClass = lootWeaponStuff.GetRandomElement();
									break;
								case 5:
									itemObjectClass = lootMelee.GetRandomElement();
									break;
								case 6:
									itemObjectClass = lootFood.GetRandomElement();
									break;
								case 7:
									itemObjectClass = lootDrink.GetRandomElement();
									break;
								case 8:
									itemObjectClass = lootBig.GetRandomElement();
									break;
							}
							
							itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
							itemObject.PlaceOnSurface();
							
						}
					}
				}
			}
			tick2 = currentTime;
		}
		
		if(currentTime >= tick3 + 60)
		{
			GetGame().ChatPlayer(5,"Sorry for all the restart, I'm working everyday on the server");
			GetGame().ChatPlayer(5,"You can contact me on discord : Bulot[hashtag]5997");
			tick3 = currentTime;
		}
		
		if(currentTime >= tick4 + 300)
		{
			GetGame().ChatPlayer(5,"Hello, Welcome to our PVE Server. It is heavily modded and still under development");
			GetGame().ChatPlayer(5,"Be sure to join this server with DayzSaLauncher to get all the mods");
			GetGame().ChatPlayer(5,"There is a lot of zombies, and you can loot them when they die");
			GetGame().ChatPlayer(5,"There is also some stuff on the ground");
			GetGame().ChatPlayer(5,"Good luck and open your eyes :)");
			tick4 = currentTime;
		}
		
		
	}
	
	string GetRandomChildFromBaseClass( string strConfigName, string strBaseClass )
	{
		string child_name = "";
		int count = GetGame().ConfigGetChildrenCount ( strConfigName );
		array<string> class_names = new array<string>;

		for (int p = 0; p < count; p++)
		{
			GetGame().ConfigGetChildName ( strConfigName, p, child_name );
			
			if ( GetGame().IsKindOf(child_name, strBaseClass ) )
			{
				class_names.Insert(child_name);
			}
		}
		return class_names.GetRandomElement();
	}
	
	vector GetRandomRadiusPos( vector posBase, int radius )
	{
		float posX = posBase[0];
        float posZ = posBase[2];
		
		int randomRadiusX = Math.RandomIntInclusive(-radius,radius);
		int radiusX = posX + randomRadiusX;
		
		int randomRadiusZ = Math.RandomIntInclusive(-radius,radius);
		int radiusZ = posZ + randomRadiusZ;
		
		int radiusY = GetGame().SurfaceY( radiusX, radiusZ );
		vector radiusPos = Vector( radiusX, radiusY, radiusZ );
		
		return radiusPos;
	}
	
	array<Object> GetAllItemsAroundPos(vector pos, int radius, bool deleteAll = false)
	{
		ref array<Object> allItems = new array<Object>;
		ref array<Object> allItemsFiltered = new array<Object>;
		GetGame().GetObjectsAtPosition(pos, radius, allItems, NULL);
		
		for (int allItems_i = 0; allItems_i < allItems.Count(); allItems_i++) 
		{
			if (allItems[allItems_i].IsKindOf("Inventory_Base") || allItems[allItems_i].IsKindOf("DefaultWeapon") || allItems[allItems_i].IsKindOf("DefaultMagazine")) 
			{
				if(deleteAll == true)
				{
					GetGame().ObjectDelete(allItems[allItems_i]);
				}
				else
				{
					allItemsFiltered.Insert(allItems[allItems_i]);
				}
			}
		}
		return allItemsFiltered;
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}

ref TStringArray lootMag = {
		"Mag_FNX45_15Rnd",
		"Mag_357Speedloader_6Rnd",
		"Mag_DE_9rnd",
		"Mag_1911_7Rnd",
		"Mag_CZ75_15Rnd",
		"Mag_Glock_15Rnd",
		"Mag_P1_8Rnd",
		"Mag_IJ70_8Rnd",
		"Mag_MP5_15Rnd",
		"Mag_MP5_30Rnd",
		"Mag_CZ61_20Rnd",
		"Mag_MKII_10Rnd",
		"Mag_Ruger1022_10Rnd",
		"Mag_Ruger1022_30Rnd",
		"Mag_CLIP762x54_5Rnd",
		"Mag_762x54Snaploader_2Rnd",
		"Mag_308WinSnaploader_2Rnd",
		"Mag_CLIP762x39_10Rnd",
		"Mag_CLIP9x19_10Rnd",
		"Mag_AKM_30Rnd",
		"Mag_AKM_Drum75Rnd",
		"Mag_CZ527_5rnd",
		"Mag_STANAG_30Rnd",
		"Mag_STANAGCoupled_30Rnd",
		"Mag_CMAG_10Rnd",
		"Mag_CMAG_20Rnd",
		"Mag_CMAG_30Rnd",
		"Mag_CMAG_40Rnd",
		"Mag_AK101_30Rnd",
		"Mag_AK74_30Rnd",
		"Mag_SVD_10Rnd",
		"Mag_FAL_20Rnd",
		"Mag_Scout_5Rnd",
		"Mag_UMP_25Rnd",
		"Mag_VSS_10Rnd",
		"Mag_M249_Box200Rnd",
		"Mag_12gaSnaploader_2Rnd",
		"Mag_Saiga_5Rnd",
		"Mag_Saiga_8Rnd",
		"Mag_Saiga_Drum20Rnd",
		"Mag_MakarovPB_8Rnd",
	};
	
	ref TStringArray lootAmmo = {
		"Ammo_45ACP",
		"Ammo_308Win",
		"Ammo_9x19",
		"Ammo_380",
		"Ammo_556x45",
		"Ammo_762x54",
		"Ammo_762x54Tracer",
		"Ammo_762x39",
		"Ammo_9x39",
		"Ammo_22",
		"Ammo_12gaPellets",
		"Ammo_12gaSlug",
		"Ammo_357",
		"Ammo_545x39",
		"AmmoBox_556x45_20Rnd",
		"AmmoBox_308Win_20Rnd",
		"AmmoBox_762x54_20Rnd",
		"AmmoBox_762x39_20Rnd",
		"AmmoBox_22_50Rnd",
		"AmmoBox_357_20Rnd",
		"AmmoBox_45ACP_25rnd",
		"AmmoBox_9x19_25rnd",
		"AmmoBox_380_35rnd",
		"AmmoBox_00buck_10rnd",
		"AmmoBox_545x39_20Rnd",
		"AmmoBox_9x39_20Rnd",
	};

	ref TStringArray lootWeapon = {
		"MakarovIJ70",
		"CZ75",
		"FNX45",
		"FNX45_arrow",
		"gp_colt1911",//Redux
		"gp_colt1911Engraved",//Redux
		"gp_MKII",//Redux
		"gp_DE",//Redux
		"gp_Glock19",//Redux
		"gp_LongHorn",//Redux
		"gp_P1",//Redux
		"gp_Ruger1022",//Redux
		//
	
		"Izh18",
		"SawedoffIzh18",
		"Mosin9130",
		"Mosin9130_Black",
		"Mosin9130_Green",
		"Mosin9130_Camo",
		"SawedoffMosin9130",
		"SawedoffMosin9130_Black",
		"SawedoffMosin9130_Green",
		"SawedoffMosin9130_Camo",
		"Mp133Shotgun",
		"gp_Blaze95",//Redux
		"gp_Saiga12kShotgun",//Redux
		"gp_Scout",//Redux
		"gp_trumpet",//Redux
		"gp_Winchester70",//Redux
		//
	
		"UMP45",
		"CZ61",
		"MP5K",
		//
	
		"gp_AK101",//Redux
		"gp_AK74",//Redux
		"gp_AKS74U",//Redux
		"gp_AugSteyr",//Redux
		"gp_FAL",//Redux
		"gp_M249",//Redux
		"gp_vss",//Redux
		"SVD",
		"AKM",
		"M4A1",
		//
	};
	
	ref TStringArray lootWeaponStuff = {
		"M4_OEBttstck",
		"M4_MPBttstck",
		"M4_CQBBttstck",
		"AK_WoodBttstck",
		"AK_FoldingBttstck",
		"AK_PlasticBttstck",
		"MP5k_StockBttstck",
		"M4_PlasticHndgrd",
		"M4_RISHndgrd",
		"M4_MPHndgrd",
		"AK_WoodHndgrd",
		"AK_RailHndgrd",
		"AK_PlasticHndgrd",
		"MP5_PlasticHndgrd",
		"MP5_RailHndgrd",
		"GhillieAtt_Tan",
		"GhillieAtt_Woodland",
		"GhillieAtt_Mossy",
		"M4_Suppressor",
		"AK_Suppressor",
		"PistolSuppressor",
		"UniversalLight",
		"TLRLight",
		"M4_CarryHandleOptic",
		"M68Optic",
		"ACOGOptic",
		"PUScopeOptic",
		"KashtanOptic",
		"GrozaOptic",
		"KobraOptic",
	};
	
	ref TStringArray lootMelee = {
		"WoodAxe",
		"Hatchet",
		"FirefighterAxe",
		"FirefighterAxe_Black",
		"FirefighterAxe_Green",
		"Cleaver",
		"CombatKnife",
		"HuntingKnife",
		"Machete",
		"Pitchfork",
		"Pickaxe",
		"Sword",
		"BaseballBat",
		"NailedBaseballBat",
		"PipeWrench",
		"BrassKnuckles_Dull",
		"BrassKnuckles_Shiny",
		"TelescopicBaton",
		"HockeyStick",
		"NewHockeyStick",
		"PoliceBaton",
		"Chainsaw",
		"CattleProd",
		"StunBaton",
		"Shovel",
		
	};
	
	ref TStringArray lootFood = {
		"BakedBeansCan",
		"BakedBeansCan_Opened",
		"PeachesCan",
		"PeachesCan_Opened",
		"TacticalBaconCan",
		"TacticalBaconCan_Opened",
		"SpaghettiCan",
		"SpaghettiCan_Opened",
		"SardinesCan",
		"SardinesCan_Opened",
		"TunaCan",
		"TunaCan_Opened",
		"Apple",
		"Banana",
		"Orange",
		"Tomato",
		"GreenBellPepper",
		"Zucchini",
		"Pumpkin",
		"SlicedPumpkin",
		"Potato",
		"Kiwi",
	};
	
	ref TStringArray lootDrink = {
		"WaterBottle",
	};

	ref TStringArray lootOther = {
		"Rope",
		"Battery9V",
		"Hammer",
		"FryingPan",
		"SparkPlug",
		"WhetStone",
		"BarbedWire",
		"MetalWire",
		"Lockpick",
		"CombinationLock",
		"DisinfectantSpray",
		"Flashlight",
		"NailBox",
		"Nail",
		"Rag",
		"Pliers",
		"Roadflare",
	};

	ref TStringArray lootBig = {
		"WoodenPlank",
		"SpotLight",
		"MetalPlate",
		"PowerGenerator",
	};
	
	ref TStringArray animalClasses = {
		"Animal_BosTaurusF_Brown",
		"Animal_BosTaurusF_Spotted",
		"Animal_BosTaurusF_White",
		"Animal_BosTaurus_Brown",
		"Animal_BosTaurus_Spotted",
		"Animal_BosTaurus_White",
		"Animal_CanisLupus_White",
		"Animal_CapraHircusF",
		"Animal_CapraHircus_Black",
		"Animal_CapraHircus_Brown",
		"Animal_CapraHircus_White",
		"Animal_CapreolusCapreolus",
		"Animal_CapreolusCapreolusF",
		"Animal_CervusElaphus",
		"Animal_CervusElaphusF",
		"Animal_GallusGallusDomesticus",
		"Animal_GallusGallusDomesticusF_Brown",
		"Animal_GallusGallusDomesticusF_Spotted",
		"Animal_GallusGallusDomesticusF_White",
		"Animal_OvisAries",
		"Animal_OvisAriesF",
		"Animal_SusDomesticus",
		"Animal_SusScrofa",
	};
	
	ref TStringArray ZombieClasses = {
		"ZmbM_HermitSkinny_Beige","ZmbM_HermitSkinny_Black","ZmbM_HermitSkinny_Green","ZmbM_HermitSkinny_Red","ZmbM_FarmerFat_Beige","ZmbM_FarmerFat_Blue","ZmbM_FarmerFat_Brown",
		"ZmbM_FarmerFat_Green","ZmbF_CitizenANormal_Beige","ZmbF_CitizenANormal_Brown",
		"ZmbF_CitizenANormal_Blue","ZmbM_CitizenASkinny_Blue","ZmbM_CitizenASkinny_Brown",
		"ZmbM_CitizenASkinny_Grey","ZmbM_CitizenASkinny_Red","ZmbM_CitizenBFat_Blue","ZmbM_CitizenBFat_Red",
		"ZmbM_CitizenBFat_Green","ZmbF_CitizenBSkinny","ZmbM_PrisonerSkinny",
		"ZmbM_FirefighterNormal","ZmbM_FishermanOld_Blue","ZmbM_FishermanOld_Green",
		"ZmbM_FishermanOld_Grey","ZmbM_FishermanOld_Red","ZmbM_JournalistSkinny",
		"ZmbF_JournalistNormal_Blue","ZmbF_JournalistNormal_Green","ZmbF_JournalistNormal_Red","ZmbF_JournalistNormal_White",
		"ZmbM_ParamedicNormal_Blue","ZmbM_ParamedicNormal_Green","ZmbM_ParamedicNormal_Red",
		"ZmbM_ParamedicNormal_Black","ZmbF_ParamedicNormal_Blue","ZmbF_ParamedicNormal_Green",
		"ZmbF_ParamedicNormal_Red","ZmbM_HikerSkinny_Blue","ZmbM_HikerSkinny_Green","ZmbM_HikerSkinny_Yellow",
		"ZmbF_HikerSkinny_Blue","ZmbF_HikerSkinny_Grey","ZmbF_HikerSkinny_Green","ZmbF_HikerSkinny_Red",
		"ZmbM_HunterOld_Autumn","ZmbM_HunterOld_Spring","ZmbM_HunterOld_Summer","ZmbM_HunterOld_Winter",
		"ZmbF_SurvivorNormal_Blue","ZmbF_SurvivorNormal_Orange","ZmbF_SurvivorNormal_Red",
		"ZmbF_SurvivorNormal_White","ZmbM_SurvivorDean_Black","ZmbM_SurvivorDean_Blue","ZmbM_SurvivorDean_Grey",
		"ZmbM_PolicemanFat","ZmbF_PoliceWomanNormal",
		"ZmbM_PolicemanSpecForce","ZmbM_SoldierNormal",
		"ZmbM_usSoldier_normal_Woodland","ZmbM_usSoldier_normal_Desert","ZmbM_CommercialPilotOld_Blue",
		"ZmbM_CommercialPilotOld_Olive","ZmbM_CommercialPilotOld_Brown","ZmbM_CommercialPilotOld_Grey",
		"ZmbM_PatrolNormal_PautRev","ZmbM_PatrolNormal_Autumn","ZmbM_PatrolNormal_Flat","ZmbM_PatrolNormal_Summer",
		"ZmbM_JoggerSkinny_Blue","ZmbM_JoggerSkinny_Green","ZmbM_JoggerSkinny_Red","ZmbF_JoggerSkinny_Blue",
		"ZmbF_JoggerSkinny_Brown","ZmbF_JoggerSkinny_Green","ZmbF_JoggerSkinny_Red","ZmbM_MotobikerFat_Beige",
		"ZmbM_MotobikerFat_Black","ZmbM_MotobikerFat_Blue","ZmbM_VillagerOld_Blue","ZmbM_VillagerOld_Green",
		"ZmbM_VillagerOld_White","ZmbM_SkaterYoung_Blue","ZmbM_SkaterYoung_Brown","ZmbM_SkaterYoung_Green",
		"ZmbM_SkaterYoung_Grey","ZmbF_SkaterYoung_Brown","ZmbF_SkaterYoung_Striped","ZmbF_SkaterYoung_Violet",
		"ZmbF_DoctorSkinny","ZmbF_BlueCollarFat_Blue","ZmbF_BlueCollarFat_Green",
		"ZmbF_BlueCollarFat_Red","ZmbF_BlueCollarFat_White","ZmbF_MechanicNormal_Beige","ZmbF_MechanicNormal_Green",
		"ZmbF_MechanicNormal_Grey","ZmbF_MechanicNormal_Orange","ZmbM_MechanicSkinny_Blue","ZmbM_MechanicSkinny_Grey",
		"ZmbM_MechanicSkinny_Green","ZmbM_MechanicSkinny_Red","ZmbM_ConstrWorkerNormal_Beige",
		"ZmbM_ConstrWorkerNormal_Black","ZmbM_ConstrWorkerNormal_Green","ZmbM_ConstrWorkerNormal_Grey",
		"ZmbM_HeavyIndustryWorker","ZmbM_OffshoreWorker_Green","ZmbM_OffshoreWorker_Orange","ZmbM_OffshoreWorker_Red",
		"ZmbM_OffshoreWorker_Yellow","ZmbF_NurseFat","ZmbM_HandymanNormal_Beige",
		"ZmbM_HandymanNormal_Blue","ZmbM_HandymanNormal_Green","ZmbM_HandymanNormal_Grey","ZmbM_HandymanNormal_White",
		"ZmbM_DoctorFat","ZmbM_Jacket_beige","ZmbM_Jacket_black","ZmbM_Jacket_blue","ZmbM_Jacket_bluechecks",
		"ZmbM_Jacket_brown","ZmbM_Jacket_greenchecks","ZmbM_Jacket_grey","ZmbM_Jacket_khaki","ZmbM_Jacket_magenta","ZmbM_Jacket_stripes",
		"ZmbF_PatientOld","ZmbM_PatientSkinny","ZmbF_ShortSkirt_beige",
		"ZmbF_ShortSkirt_black","ZmbF_ShortSkirt_brown","ZmbF_ShortSkirt_green","ZmbF_ShortSkirt_grey","ZmbF_ShortSkirt_checks",
		"ZmbF_ShortSkirt_red","ZmbF_ShortSkirt_stripes","ZmbF_ShortSkirt_white","ZmbF_ShortSkirt_yellow",
		"ZmbF_VillagerOld_Blue","ZmbF_VillagerOld_Green","ZmbF_VillagerOld_Red","ZmbF_VillagerOld_White","ZmbM_Soldier","ZmbM_SoldierAlice",
		"ZmbM_SoldierHelmet","ZmbM_SoldierVest","ZmbM_SoldierAliceHelmet","ZmbM_SoldierVestHelmet",
		"ZmbF_MilkMaidOld_Beige","ZmbF_MilkMaidOld_Black","ZmbF_MilkMaidOld_Green","ZmbF_MilkMaidOld_Grey",
		"ZmbM_priestPopSkinny","ZmbM_ClerkFat_Brown","ZmbM_ClerkFat_Grey","ZmbM_ClerkFat_Khaki","ZmbM_ClerkFat_White","ZmbF_Clerk_Normal_Blue","ZmbF_Clerk_Normal_White","ZmbF_Clerk_Normal_Green","ZmbF_Clerk_Normal_Red",
	};

//To save
/*
Object itemObject;
							string itemObjectClass;
							string itemObjectDisplayName;
							switch(Math.RandomIntInclusive(0,0))
							{
								case 0:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "Inventory_Base");
									itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 1:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "Inventory_Base");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 2:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "Inventory_Base");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 3:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "Inventory_Base");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 4:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "DefaultMagazine");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);	
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 5:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "DefaultMagazine");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);	
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 6:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "DefaultMagazine");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
								case 7:
									itemObjectClass = GetRandomChildFromBaseClass("cfgVehicles", "DefaultWeapon");
									itemObject = GetGame().CreateObject(itemObjectClass,player.GetPosition());
									itemObjectDisplayName = itemObject.GetDisplayName();
									GetGame().ObjectDelete(itemObject);	
									if(itemObjectDisplayName.Contains("$") == false)
									{
										itemObject = GetGame().CreateObject(itemObjectClass,GetRandomRadiusPos(nearestBuildings[nearestBuildings_i].GetPosition(),5));
									}
									break;
							}
*/