class CfgPatches
{
	class testMod_scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			//"DZ_Characters"
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class testMod
	{
	    dir = "testMod";
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = "testMod";
	    credits = "Bulot";
	    author = "Bulot";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    //dependencies[] = {"World"};
			dependencies[] = {"World","Mission"};

		class defs
		{
			class worldScriptModule
			{
				value = "";
               			files[] = {"bulot/scripts/4_World"};
            		};
			class missionScriptModule
			{
				value = "";
               			files[] = {"bulot/scripts/5_Mission"};
            		};
        };
    };
};
