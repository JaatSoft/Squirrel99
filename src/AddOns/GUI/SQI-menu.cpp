/*
 * Squirrel project
 *
 * file ?	SQI-menu.cpp
 * what	?   menu object
 * who	?	jlv
 * when	?	12/08/99
 * last	?	02/16/01
 *
 *
 * (c) Kirilla 1999-2001
 */
 
#include "Colors.h"
#include "SQI-AddOn.h"
#include "SQI-utils.h"
#include "SQI-widget.h"
#include "SQI-bwidget.h"
#include "SQI-bmenu.h"
#include "SQI-glue.h"
#include "SQI-menu.h"
#include "SQI-bwindow.h"
#include "SQI-font.h"
#include "SQI-menuitem.h"
     
/*
 * function    : SQI_Menu
 * purpose     : Constructor
 * input       : 
 *
 * BRect frame, view frame
 * uint32 resizingMode, resizing mode
 * uint32 flags, flags
 *
 * output      : none
 * side effect : none
 */
SQI_Menu::SQI_Menu(SQI_Interp *interp,SQI_BMenu *ptr,const char *label)
	:BMenu(label) , 
	SQI_Widget(ptr)
{	
	Interpreter = interp;
	MagicPtr = ptr;
}


/*
 * function    : ~SQI_Menu
 * purpose     : Menu destructor
 * input       : none
 * output      : none
 * side effect : none
 */
SQI_Menu::~SQI_Menu()
{
} 

// Hooks

/*
 * function    : AttachedToWindow
 * purpose     : Called when the view is attached to a window
 * input       : none
 * output      : none
 * side effect : none
 */
void SQI_Menu::AttachedToWindow(void)
{							
	if(Supermenu())
	{
		// now we set the bgcolor and the font to the same that the
		// parent if not allready set by the user
				
		if(!hcolor_set)
			SetHighColor(Supermenu()->HighColor());
		if(!lcolor_set)	
			SetLowColor(Supermenu()->LowColor());
		if(!bgcolor_set)	
			SetViewColor(Supermenu()->ViewColor());
		if(!font_set)
		{	
			BFont font;
			Supermenu()->GetFont(&font);
			SetFont(&font);	
		}	
	}										
	
	BMenu::AttachedToWindow();		
}

// Cloning methods

/*
 * function    : Clone
 * purpose     : Set a cloned view to be the same
 * input       : 
 *
 * SQI_Menu *clone, cloned view
 *
 * output      : none
 * side effect : none
 */
void SQI_Menu::Clone(SQI_Menu *clone)
{	
	// first we call the methods of SQI_Widget
	
	SQI_Widget::Clone(clone);
	
	// now we set the specific setting of a Menu
	
	// the font used
	
	BFont font;
	GetFont(&font);					
	clone->SetFont(&font);
	
	// Drawing mode		
	
	clone->SetDrawingMode(DrawingMode());
	
	// color
	
	clone->SetHighColor(HighColor());
	clone->SetLowColor(LowColor());
	clone->SetViewColor(ViewColor());
	
	// that's all	
}

void SQI_Menu::DelCallBack()
{
	BMenu *submenu;
	SQI_Menu *sub;
	SQI_MenuItem *item;	
	
	// loop on all the menuitem and delete the callback of it
	for(int32 i=0;i<CountItems();i++)
 	{
 		submenu = SubmenuAt(i);
 		if(submenu)
 		{	
 			sub = dynamic_cast<SQI_Menu *>(submenu);
 			if(sub)
 				sub->DelCallBack();
 		}
 		else
 		{
 			item = dynamic_cast<SQI_MenuItem *>(ItemAt(i));
 			if(item)
 				item->DelCallBack();	 			
 		}
 	}
}


