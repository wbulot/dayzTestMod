class welcomeMessage extends UIScriptedMenu
{
	protected TextListboxWidget your_text;
	protected ButtonWidget your_button;

	void welcomeMessage()
	{
		Print("[bulot]welcomeMessage init");
	}

	void ~welcomeMessage()
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
        GetGame().GetUIManager().ShowUICursor(true);
        GetGame().GetUIManager().ShowCursor(true);
		Print( "[bulot]Welcome message OnShow" );
		
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
}