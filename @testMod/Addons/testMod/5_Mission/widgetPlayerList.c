class widgetPlayerList extends UIScriptedMenu
{
	protected TextListboxWidget your_text;
	protected ButtonWidget your_button;

	void widgetPlayerList()
	{
		Print("[bulot]widgetPlayerList init");
		GetRPCManager().AddRPC( "testMod", "MyFunction", this, SingeplayerExecutionType.Client );
		GetRPCManager().AddRPC( "testMod", "MyFunction2", this, SingeplayerExecutionType.Client );
	}

	void ~widgetPlayerList()
	{

	}

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "bulot/scripts/layouts/widget.layout" );

		your_text = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("WidgetTextListbox"));

		your_button = ButtonWidget.Cast( layoutRoot.FindAnyWidget("WidgetButton"));

		return layoutRoot;
	}

	override void OnShow()
	{
	    super.OnShow();
		GetRPCManager().SendRPC( "testMod", "MyFunction", new Param, true);
	}

	override void OnHide()
	{
		super.OnHide();

	}

	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange( w, x, y, finished );

		return false;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		if(w == your_button)
		{
			
		}
        return false;
	}

	void MyFunction(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		ref Param2< ref array<Man>, ref array<string> > data;
		if ( !ctx.Read( data ) ) return;
		
		ref array<Man> arr = new ref array<Man>;
		arr.Copy( data.param1 );
		ref array<string> arr2 = new ref array<string>;
		arr2.Copy( data.param2 );
		
		if( type == CallType.Client )
        {
            Print( "[bulot]Client function called through RPC!" );
			
			//for ( int i = 0; i < arr.Count(); ++i )
			//{
			//	your_text.AddItem(arr[i].GetIdentity().GetName(), NULL, 0 );
			//}
			
			for ( int i2 = 0; i2 < arr2.Count(); ++i2 )
			{
				your_text.AddItem(arr2[i2], NULL, 0 );
			}
        }
	}
	
	void MyFunction2(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if( type == CallType.Client )
        {
            Print( "[bulot]Client function called through RPC OnEvent ClientReadyEventTypeID" );
        }
	}
}