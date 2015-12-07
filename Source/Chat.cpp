/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/

//[Headers] You can add your own extra header files here...

#include "AvCaster.h"
#include "Trace/TraceChat.h"

//[/Headers]

#include "Chat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Chat::Chat ()
{
    addAndMakeVisible (chatGroup = new GroupComponent ("chatGroup",
                                                       TRANS("Chat")));
    chatGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatHistoryGroup = new GroupComponent ("chatHistoryGroup",
                                                              String::empty));
    chatHistoryGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatHistoryGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatHistoryText = new TextEditor ("chatHistoryText"));
    chatHistoryText->setMultiLine (true);
    chatHistoryText->setReturnKeyStartsNewLine (false);
    chatHistoryText->setReadOnly (true);
    chatHistoryText->setScrollbarsShown (true);
    chatHistoryText->setCaretVisible (false);
    chatHistoryText->setPopupMenuEnabled (true);
    chatHistoryText->setColour (TextEditor::textColourId, Colours::white);
    chatHistoryText->setColour (TextEditor::backgroundColourId, Colours::black);
    chatHistoryText->setText (String::empty);

    addAndMakeVisible (chatEntryGroup = new GroupComponent ("chatEntryGroup",
                                                            String::empty));
    chatEntryGroup->setExplicitFocusOrder (1);
    chatEntryGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatEntryGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatEntryText = new TextEditor ("chatEntryText"));
    chatEntryText->setExplicitFocusOrder (2);
    chatEntryText->setMultiLine (false);
    chatEntryText->setReturnKeyStartsNewLine (false);
    chatEntryText->setReadOnly (false);
    chatEntryText->setScrollbarsShown (false);
    chatEntryText->setCaretVisible (true);
    chatEntryText->setPopupMenuEnabled (true);
    chatEntryText->setColour (TextEditor::textColourId, Colours::white);
    chatEntryText->setColour (TextEditor::backgroundColourId, Colour (0xff202020));
    chatEntryText->setText (String::empty);

    addAndMakeVisible (chatList = new ChatList());
    chatList->setExplicitFocusOrder (2);
    chatList->setName ("chatList");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  // defer visibility until connected to some chat channel
  updateVisiblilty() ;

  // text editor colors
  this->chatEntryText  ->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  this->chatHistoryText->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->chatEntryText  ->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->chatHistoryText->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatEntryText  ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatHistoryText->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatEntryText  ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatHistoryText->setColour(TextEditor::outlineColourId         , GUI::TEXT_BG_COLOR      ) ;
  this->chatEntryText  ->setColour(TextEditor::outlineColourId         , GUI::TEXT_BG_COLOR      ) ;
  this->chatHistoryText->setColour(TextEditor::focusedOutlineColourId  , GUI::TEXT_FOCUS_COLOR   ) ;
  this->chatEntryText  ->setColour(TextEditor::focusedOutlineColourId  , GUI::TEXT_FOCUS_COLOR   ) ;
  this->chatHistoryText->setColour(TextEditor::shadowColourId          , GUI::TEXT_SHADOW_COLOR  ) ;
  this->chatEntryText  ->setColour(TextEditor::shadowColourId          , GUI::TEXT_SHADOW_COLOR  ) ;
  this->chatHistoryText->setColour(TextEditor::backgroundColourId      , GUI::TEXT_BG_COLOR      ) ;
  this->chatEntryText  ->setColour(TextEditor::backgroundColourId      , GUI::TEXT_BG_COLOR      ) ;

  // text editor behaviors
  this->chatEntryText->setSelectAllWhenFocused(true) ;
  this->chatEntryText->setTextToShowWhenEmpty(GUI::CHAT_PROMPT_TEXT , GUI::TEXT_EMPTY_COLOR) ;
  this->chatEntryText->setInputRestrictions(1024) ;

  // local event handlers
  this->chatEntryText->addListener(this) ;

    //[/Constructor]
}

Chat::~Chat()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chatGroup = nullptr;
    chatHistoryGroup = nullptr;
    chatHistoryText = nullptr;
    chatEntryGroup = nullptr;
    chatEntryText = nullptr;
    chatList = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Chat::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Chat::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    chatGroup->setBounds (16, 8, getWidth() - 32, getHeight() - 24);
    chatHistoryGroup->setBounds (28, 22, getWidth() - 56, getHeight() - 90);
    chatHistoryText->setBounds (32, 32, getWidth() - 64, getHeight() - 104);
    chatEntryGroup->setBounds (28, getHeight() - 68, getWidth() - 56, 38);
    chatEntryText->setBounds (32, getHeight() - 58, getWidth() - 64, 24);
    chatList->setBounds (getWidth() - 160, 32, 128, 256);
    //[UserResized] Add your own custom resize handling here..

  chatList->setBounds(getWidth() - GUI::LIST_X , GUI::LIST_Y , GUI::LIST_W , GUI::LIST_H) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Chat public instance methods */

void Chat::updateVisiblilty()
{
  bool   is_visible  = this->chattersStore.getNumChildren() > 0 ;
  String group_title = (is_visible) ? GUI::CHAT_GROUP_TITLE : AvCaster::GetVersionString() ;

DEBUG_TRACE_CHAT_VISIBILITY

  this->chatGroup       ->setText   (group_title) ;
  this->chatHistoryGroup->setVisible(is_visible) ;
  this->chatHistoryText ->setVisible(is_visible) ;
  this->chatEntryGroup  ->setVisible(is_visible) ;
  this->chatEntryText   ->setVisible(is_visible) ;
  this->chatList        ->setVisible(is_visible) ;
}

void Chat::addChatLine(String nick , String message_text)
{
  String message_header = (nick == GUI::SERVER_NICK) ? "" : nick + ": " ;

  const MessageManagerLock mmLock ;
  this->chatHistoryText->moveCaretToEnd() ;
  this->chatHistoryText->insertTextAtCaret("\n" + message_header + message_text) ;
}


/* Chat private instance methods */

void Chat::initialize(ValueTree chatters_store)
{
  this->chatList->chattersStore = this->chattersStore = chatters_store ;
}

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  if (&a_text_editor != this->chatEntryText) return ;

  AvCaster::SendChat(this->chatEntryText->getText()) ;
  this->chatEntryText->clear() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Chat" componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1"
                 initialHeight="1">
  <BACKGROUND backgroundColour="ff101010"/>
  <GROUPCOMPONENT name="chatGroup" id="6607ba656d5c8919" memberName="chatGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 8 32M 24M" outlinecol="ffffffff"
                  textcol="ffffffff" title="Chat"/>
  <GROUPCOMPONENT name="chatHistoryGroup" id="258cc166964ef054" memberName="chatHistoryGroup"
                  virtualName="" explicitFocusOrder="0" pos="28 22 56M 90M" outlinecol="ffffffff"
                  textcol="ffffffff" title=""/>
  <TEXTEDITOR name="chatHistoryText" id="f98355c5e336ef72" memberName="chatHistoryText"
              virtualName="" explicitFocusOrder="0" pos="32 32 64M 104M" textcol="ffffffff"
              bkgcol="ff000000" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <GROUPCOMPONENT name="chatEntryGroup" id="da473ae049822d5c" memberName="chatEntryGroup"
                  virtualName="" explicitFocusOrder="1" pos="28 68R 56M 38" outlinecol="ffffffff"
                  textcol="ffffffff" title=""/>
  <TEXTEDITOR name="chatEntryText" id="1dd802ce165b4013" memberName="chatEntryText"
              virtualName="" explicitFocusOrder="2" pos="32 58R 64M 24" textcol="ffffffff"
              bkgcol="ff202020" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <GENERICCOMPONENT name="chatList" id="90795555172fbed0" memberName="chatList" virtualName=""
                    explicitFocusOrder="2" pos="160R 32 128 256" class="ChatList"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]