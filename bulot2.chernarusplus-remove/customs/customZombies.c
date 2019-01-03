class customZombies
{
	
	ref array<EntityAI> zombiesSpawned = new array<EntityAI>;
	ref array<int> zombiesSpawnedTime = new array<int>;
	ref array<int> zombiesSpawnedDeadTime = new array<int>;
	
	ref array<EntityAI> animalsSpawned = new array<EntityAI>;
	ref array<int> animalsSpawnedTime = new array<int>;
	ref array<int> animalsSpawnedDeadTime = new array<int>;
	
	ref array<EntityAI> carsSpawned = new array<EntityAI>;
	ref array<int> carsSpawnedTime = new array<int>;
	
	ref array<Man> players = new array<Man>;
	void customZombies()
	{
		
	}
	
	void CreateZombies(int number, vector ZmbPos)
	{
		for ( int i = 0; i < number; ++i )
		{
			int currentTime = GetGame().GetTime() * 0.001;
			string zmbClass = ZombieClasses.GetRandomElement();
			
			EntityAI AIzmb = GetGame().CreateObject(zmbClass,ZmbPos,false,true);
			
			int dropSelect = Math.RandomIntInclusive(0,7);
			if(dropSelect == 0)
			{
				AIzmb.GetInventory().CreateInInventory(lootOther.GetRandomElement());
			}
			else if(dropSelect == 1)
			{
				AIzmb.GetInventory().CreateInInventory(lootMag.GetRandomElement());
				
			}
			else if(dropSelect == 2)
			{
				AIzmb.GetInventory().CreateInInventory(lootAmmo.GetRandomElement());
			}
			else if(dropSelect == 3)
			{
				AIzmb.GetInventory().CreateInInventory(lootMelee.GetRandomElement());
			}
			else if(dropSelect == 4)
			{
				AIzmb.GetInventory().CreateInInventory(lootFood.GetRandomElement());
			}
			else if(dropSelect == 5)
			{
				AIzmb.GetInventory().CreateInInventory(lootDrink.GetRandomElement());
			}
			else if(dropSelect == 6)
			{
				AIzmb.GetInventory().CreateInInventory(lootWeaponStuff.GetRandomElement());
			}
			else if(dropSelect == 7)
			{
				AIzmb.GetInventory().CreateInInventory(lootWeapon.GetRandomElement());
			}
			
			zombiesSpawned.Insert(AIzmb);
			zombiesSpawnedTime.Insert(currentTime);
			zombiesSpawnedDeadTime.Insert(0);
		}
	}
	
	void CreateAnimals(int number, vector anmlPos)
	{
		for ( int i = 0; i < number; ++i )
		{
			int currentTime = GetGame().GetTime() * 0.001;
			string anmlClass = animalClasses.GetRandomElement();
			
			EntityAI AIanml = GetGame().CreateObject(anmlClass,anmlPos,false,true);

			animalsSpawned.Insert(AIanml);
			animalsSpawnedTime.Insert(currentTime);
			animalsSpawnedDeadTime.Insert(0);
		}
	}
	
	void CreateCars(int number, vector carPos)
	{
		for ( int i = 0; i < number; ++i )
		{
			int currentTime = GetGame().GetTime() * 0.001;
			string carClass = "OffroadHatchback";
			
			Car car = GetGame().CreateObject(carClass,carPos,false,true);
			car.GetInventory().CreateAttachment("HatchbackTrunk");
			car.GetInventory().CreateAttachment("HatchbackDoors_Driver");
			car.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
			car.GetInventory().CreateAttachment("HatchbackWheel");
			car.GetInventory().CreateAttachment("HatchbackWheel");
			car.GetInventory().CreateAttachment("HatchbackWheel");
			car.GetInventory().CreateAttachment("HatchbackWheel");
			car.GetInventory().CreateAttachment("CarBattery");
			car.GetInventory().CreateAttachment("CarRadiator");
			car.GetInventory().CreateAttachment("EngineBelt");
			car.GetInventory().CreateAttachment("SparkPlug");
			
			float fuelReq = car.GetFluidCapacity( CarFluid.FUEL ) - (car.GetFluidCapacity( CarFluid.FUEL ) * car.GetFluidFraction( CarFluid.FUEL ));
			float oilReq = car.GetFluidCapacity( CarFluid.OIL ) - (car.GetFluidCapacity( CarFluid.OIL ) * car.GetFluidFraction( CarFluid.OIL ));
			float coolantReq = car.GetFluidCapacity( CarFluid.COOLANT ) - (car.GetFluidCapacity( CarFluid.COOLANT ) * car.GetFluidFraction( CarFluid.COOLANT ));
			float brakeReq = car.GetFluidCapacity( CarFluid.BRAKE ) - (car.GetFluidCapacity( CarFluid.BRAKE ) * car.GetFluidFraction( CarFluid.BRAKE ));
			
			car.Fill( CarFluid.FUEL, fuelReq );
			car.Fill( CarFluid.OIL, oilReq );
			car.Fill( CarFluid.COOLANT, coolantReq );
			car.Fill( CarFluid.BRAKE, brakeReq );
			
			carsSpawned.Insert(car);
			carsSpawnedTime.Insert(currentTime);
		}
	}
	
	void spawnZombies()
	{
		int currentTime = GetGame().GetTime() * 0.001;
		GetGame().GetPlayers(players);
		
		for ( int players_i = 0; players_i < players.Count(); ++players_i )
		{
			Man player = players.Get(players_i);
			
			//Player position
			vector pos = player.GetPosition();
			float posX = pos[0];
	        float posZ = pos[2];
			
			int zombiesArroundPlayer = 0;
			for (int zombiesSpawned_i2 = 0; zombiesSpawned_i2 < zombiesSpawned.Count(); ++zombiesSpawned_i2)
			{
				EntityAI zmb2 = zombiesSpawned.Get(zombiesSpawned_i2);
				float distanceZmbMan2 = vector.Distance(zmb2.GetPosition(),player.GetPosition());
				if(distanceZmbMan2 < 500)
				{
					++zombiesArroundPlayer;
				}
			}
			
			int intPosXRadius1;
			int intPosXRadius2;
			int intPosZRadius1;
			int intPosZRadius2;
			int radiusX;
			int radiusZ;
			int radiusY;
			vector ZmbPos;
			int ZNumber;
			
			if(zombiesArroundPlayer < 75)
			{
				for ( int pass_i = 0; pass_i < 10; ++pass_i )//We speed up the zombies creation process
				{
					// XXm radius
					intPosXRadius1 = posX - 400;
					intPosXRadius2 = posX + 400;
					intPosZRadius1 = posZ - 400;
					intPosZRadius2 = posZ + 400;
					
					radiusX = Math.RandomIntInclusive(intPosXRadius1,intPosXRadius2);
					radiusZ = Math.RandomIntInclusive(intPosZRadius1,intPosZRadius2);
					radiusY = GetGame().SurfaceY( radiusX, radiusZ );
					
					ZmbPos = Vector( radiusX, radiusY, radiusZ );
		
					ZNumber = Math.RandomIntInclusive(1,10);
					CreateZombies(1,ZmbPos);
				}
				
			}
			else if(zombiesArroundPlayer < 200)
			{
				// XXm radius
				intPosXRadius1 = posX - 400;
				intPosXRadius2 = posX + 400;
				intPosZRadius1 = posZ - 400;
				intPosZRadius2 = posZ + 400;
				
				radiusX = Math.RandomIntInclusive(intPosXRadius1,intPosXRadius2);
				radiusZ = Math.RandomIntInclusive(intPosZRadius1,intPosZRadius2);
				radiusY = GetGame().SurfaceY( radiusX, radiusZ );
				
				ZmbPos = Vector( radiusX, radiusY, radiusZ );
	
				ZNumber = Math.RandomIntInclusive(1,10);
				CreateZombies(ZNumber,ZmbPos);
			}

			
		}
		Print("[bulot]"+zombiesSpawned.Count().ToString() + " zombies spawned");
		
		for (int zombiesSpawned_i = 0; zombiesSpawned_i < zombiesSpawned.Count(); ++zombiesSpawned_i)
		{
			int toDelete = 1;
			EntityAI zmb = zombiesSpawned.Get(zombiesSpawned_i);
			int zmbTime = zombiesSpawnedTime.Get(zombiesSpawned_i);
			int zmbDeadTime = zombiesSpawnedDeadTime.Get(zombiesSpawned_i);
			
			if(zmb.IsAlive() == false) //If zombie is dead
			{
				//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" is dead for "+zmbDeadTime.ToString()+" sec");
				if(zmbDeadTime == 0)//If we didnt yet save his dead time, we do it
				{
					zombiesSpawnedDeadTime[zombiesSpawned_i] = currentTime;
					toDelete = 0;
				}
				else//If his dead time is already registed (basically the Z is dead for a long time)
				{
					if(currentTime - zmbDeadTime > 240)//If it's more than xx sec, we remove it
					{
						//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" to deleted>240");
						
					}
					else//Cooldown not reach, We keep that Z
					{
						toDelete = 0;
					}
				}
			}
			else //Z is alive
			{
				for ( players_i = 0; players_i < players.Count(); ++players_i )
				{
					player = players.Get(players_i);
					float distanceZmbMan = vector.Distance(zmb.GetPosition(),player.GetPosition());
					//GetGame().ChatPlayer(5,"Distance between Zmb"+zombiesSpawned_i+ "and "+player.GetIdentity().GetName()+" is : "+distanceZmbMan.ToString());
					
					if(distanceZmbMan > 500)
					{
						//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" to delete because distance is : "+distanceZmbMan.ToString());
					}
					else
					{
						toDelete = 0;
					}
				}
			}
			if(toDelete == 1)
			{
				GetGame().ObjectDelete(zmb);
				zombiesSpawned.Remove(zombiesSpawned_i);
				zombiesSpawnedDeadTime.Remove(zombiesSpawned_i);
				//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" deleted");
			}
		}
	}
	
	void spawnAnimals()
	{
		int currentTime = GetGame().GetTime() * 0.001;
		GetGame().GetPlayers(players);
		
		for ( int players_i = 0; players_i < players.Count(); ++players_i )
		{
			Man player = players.Get(players_i);
			
			//Player position
			vector pos = player.GetPosition();
			float posX = pos[0];
	        float posZ = pos[2];
			
			int animalsArroundPlayer = 0;
			for (int animalsSpawned_i2 = 0; animalsSpawned_i2 < animalsSpawned.Count(); ++animalsSpawned_i2)
			{
				EntityAI anml2 = animalsSpawned.Get(animalsSpawned_i2);
				float distanceAnmlMan2 = vector.Distance(anml2.GetPosition(),player.GetPosition());
				if(distanceAnmlMan2 < 500)
				{
					++animalsArroundPlayer;
				}
			}
			
			int intPosXRadius1;
			int intPosXRadius2;
			int intPosZRadius1;
			int intPosZRadius2;
			int radiusX;
			int radiusZ;
			int radiusY;
			vector AnmlPos;
			int ANumber;
			
			if(animalsArroundPlayer < 10)
			{
				for ( int pass_i = 0; pass_i < 10; ++pass_i )//We speed up the zombies creation process
				{
					// XXm radius
					intPosXRadius1 = posX - 400;
					intPosXRadius2 = posX + 400;
					intPosZRadius1 = posZ - 400;
					intPosZRadius2 = posZ + 400;
					
					radiusX = Math.RandomIntInclusive(intPosXRadius1,intPosXRadius2);
					radiusZ = Math.RandomIntInclusive(intPosZRadius1,intPosZRadius2);
					radiusY = GetGame().SurfaceY( radiusX, radiusZ );
					
					AnmlPos = Vector( radiusX, radiusY, radiusZ );
		
					ANumber = Math.RandomIntInclusive(1,10);
					CreateAnimals(1,AnmlPos);
				}
				
			}
			else if(animalsArroundPlayer < 15)
			{
				// XXm radius
				intPosXRadius1 = posX - 400;
				intPosXRadius2 = posX + 400;
				intPosZRadius1 = posZ - 400;
				intPosZRadius2 = posZ + 400;
				
				radiusX = Math.RandomIntInclusive(intPosXRadius1,intPosXRadius2);
				radiusZ = Math.RandomIntInclusive(intPosZRadius1,intPosZRadius2);
				radiusY = GetGame().SurfaceY( radiusX, radiusZ );
				
				AnmlPos = Vector( radiusX, radiusY, radiusZ );
	
				ANumber = Math.RandomIntInclusive(1,10);
				CreateAnimals(1,AnmlPos);
			}

			
		}
		
		//GetGame().ChatPlayer(5,animalsSpawned.Count().ToString() + " animals spawned");
		
		for (int animalsSpawned_i = 0; animalsSpawned_i < animalsSpawned.Count(); ++animalsSpawned_i)
		{
			int toDelete = 1;
			EntityAI anml = animalsSpawned.Get(animalsSpawned_i);
			int anmlTime = animalsSpawnedTime.Get(animalsSpawned_i);
			int anmlDeadTime = animalsSpawnedDeadTime.Get(animalsSpawned_i);
			
			if(anml.IsAlive() == false) //If zombie is dead
			{
				//GetGame().ChatPlayer(5,"Zmb"+animalsSpawned_i+" is dead for "+zmbDeadTime.ToString()+" sec");
				if(anmlDeadTime == 0)//If we didnt yet save his dead time, we do it
				{
					animalsSpawnedDeadTime[animalsSpawned_i] = currentTime;
					toDelete = 0;
				}
				else//If his dead time is already registed (basically the Z is dead for a long time)
				{
					if(currentTime - anmlDeadTime > 600)//If it's more than xx sec, we remove it
					{
						//GetGame().ChatPlayer(5,"Zmb"+animalsSpawned_i+" deleted");
						
					}
					else//Cooldown not reach, We keep that Z
					{
						toDelete = 0;
					}
				}
			}
			else //Z is alive
			{
				for ( players_i = 0; players_i < players.Count(); ++players_i )
				{
					player = players.Get(players_i);
					float distanceAnmlMan = vector.Distance(anml.GetPosition(),player.GetPosition());
					//GetGame().ChatPlayer(5,"Distance between Zmb"+zombiesSpawned_i+ "and "+player.GetIdentity().GetName()+" is : "+distanceZmbMan.ToString());
					
					if(distanceAnmlMan > 500)
					{
						//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" to delete because distance is : "+distanceZmbMan.ToString());
					}
					else
					{
						toDelete = 0;
					}
				}
			}
			if(toDelete == 1)
			{
				GetGame().ObjectDelete(anml);
				animalsSpawned.Remove(animalsSpawned_i);
				animalsSpawnedDeadTime.Remove(animalsSpawned_i);
				//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" deleted");
			}
		}
	}
	
	void spawnCars()
	{
		int currentTime = GetGame().GetTime() * 0.001;
		GetGame().GetPlayers(players);
		
		for ( int players_i = 0; players_i < players.Count(); ++players_i )
		{
			Man player = players.Get(players_i);
			
			//Player position
			vector pos = player.GetPosition();
			float posX = pos[0];
	        float posZ = pos[2];
			

			int carsArroundPlayer = 0;
			for (int carsSpawned_i2 = 0; carsSpawned_i2 < carsSpawned.Count(); ++carsSpawned_i2)
			{
				EntityAI car2 = carsSpawned.Get(carsSpawned_i2);
				float distanceCarMan2 = vector.Distance(car2.GetPosition(),player.GetPosition());
				if(distanceCarMan2 < 500)
				{
					++carsArroundPlayer;
				}
			}
			
			int intPosXRadius1;
			int intPosXRadius2;
			int intPosZRadius1;
			int intPosZRadius2;
			int radiusX;
			int radiusZ;
			int radiusY;
			vector CarPos;
			int CNumber;
			
			if(carsArroundPlayer < 10)
			{
				// XXm radius
				intPosXRadius1 = posX - 400;
				intPosXRadius2 = posX + 400;
				intPosZRadius1 = posZ - 400;
				intPosZRadius2 = posZ + 400;
				
				radiusX = Math.RandomIntInclusive(intPosXRadius1,intPosXRadius2);
				radiusZ = Math.RandomIntInclusive(intPosZRadius1,intPosZRadius2);
				radiusY = GetGame().SurfaceY( radiusX, radiusZ );
				
				CarPos = Vector( radiusX, radiusY, radiusZ );
	
				CNumber = Math.RandomIntInclusive(1,1);
				CreateCars(1,CarPos);
			}
		}
		
		//GetGame().ChatPlayer(5,zombiesSpawned.Count().ToString() + " zombies spawned");
		
		for (int carsSpawned_i = 0; carsSpawned_i < carsSpawned.Count(); ++carsSpawned_i)
		{
			int toDelete = 1;
			EntityAI car = carsSpawned.Get(carsSpawned_i);
			int carTime = carsSpawnedTime.Get(carsSpawned_i);
			
				for ( players_i = 0; players_i < players.Count(); ++players_i )
				{
					player = players.Get(players_i);
					float distanceCarMan = vector.Distance(car.GetPosition(),player.GetPosition());
					//GetGame().ChatPlayer(5,"Distance between Zmb"+zombiesSpawned_i+ "and "+player.GetIdentity().GetName()+" is : "+distanceZmbMan.ToString());
					
					if(distanceCarMan > 500)
					{
						//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" to delete because distance is : "+distanceZmbMan.ToString());
					}
					else
					{
						toDelete = 0;
					}
				}
			
			if(toDelete == 1)
			{
				GetGame().ObjectDelete(car);
				carsSpawned.Remove(carsSpawned_i);
				//GetGame().ChatPlayer(5,"Zmb"+zombiesSpawned_i+" deleted");
			}
		}
	}
	
};