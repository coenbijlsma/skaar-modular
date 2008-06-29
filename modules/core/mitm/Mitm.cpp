#include "Mitm.h"
#include "StringTokenizer.h"

#include "IRCMessage.h"
#include "QuitMessage.h"
#include "NickMessage.h"
#include "PassMessage.h"
#include "UserMessage.h"
#include "PrivmsgMessage.h"
#include "JoinMessage.h"
#include "OperMessage.h"
#include "PartMessage.h"
#include "ModeMessage.h"
#include "TopicMessage.h"
#include "NamesMessage.h"
#include "ListMessage.h"
#include "InviteMessage.h"
#include "KickMessage.h"
#include "VersionMessage.h"
#include "StatsMessage.h"
#include "LinksMessage.h"
#include "TraceMessage.h"
#include "AdminMessage.h"
#include "InfoMessage.h"
#include "NoticeMessage.h"
#include "WhoMessage.h"
#include "WhoisMessage.h"
#include "WhowasMessage.h"
#include "PongMessage.h"
#include "PingMessage.h"
#include "AwayMessage.h"

Mitm::Mitm(string raw){
    if(raw.at(0) != '/'){
	throw string("Invalid string: ") + _raw;
    }
    
    _raw = raw;
}

Mitm::~Mitm(){
    if(_translation != 0){
	delete _translation;
    }
}

IRCMessage* Mitm::translate(){
    if(_translation != 0){
	return _translation;
    }
    
    StringTokenizer st	= StringTokenizer(_raw, ' ');
    string _command 	= string(st.next());
    string _rawNoCmd	= _raw.substr(_command.size());
    IRCMessage* _tmp	= 0;
    
    _command 		= _command.substr(1);
    
    
    if(_skaar->isAliasFor(_command, QUITMESSAGE_COMMAND){
	_tmp = new QuitMessage( string(QUITMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, NICKMESSAGE_COMMAND){
	_tmp = new NickMessage( string(NICKMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, PASSMESSAGE_COMMAND){
	_tmp = new PassMessage( string(PASSMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, USERMESSAGE_COMMAND){
	_tmp = new UserMessage( string(USERMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, PRIVMSGMESSAGE_COMMAND){
	_tmp = new PrivmsgMessage( string(PRIVMSGMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, JOINMESSAGE_COMMAND){
	_tmp = new JoinMessage( string(JOINMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, OPERMESSAGE_COMMAND){
	_tmp = new OperMessage( string(OPERMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, PARTMESSAGE_COMMAND){
	_tmp = new PartMessage( string(PARTMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, MODEMESSAGE_COMMAND){
	_tmp = new ModeMessage( string(MODEMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isALiasFor(_command, TOPICMESSAGE_COMMAND){
	_tmp = new TopicMessage( string(TOPICMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, NAMESMESSAGE_COMMAND){
	_tmp = new NamesMessage( string(NAMESMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, LISTMESSAGE_COMMAND){
	_tmp = new ListMessage( string(LISTMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, INVITEMESSAGE_COMMAND){
	_tmp = new InviteMessage( string(INVITEMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, KICKMESSAGE_COMMAND){
	_tmp = new KickMessage( string(KICKMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, VERSIONMESSAGE_COMMAND){
	_tmp = new VersionMessage( string(VERSIONMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, STATSMESSAGE_COMMAND){
	_tmp = new StatsMessage( string(STATSMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, LINKSMESSAGE_COMMAND){
	_tmp = new LinksMessage( string(LINKSMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, TRACEMESSAGE_COMMAND){
	_tmp = new TraceMessage( string(TRACEMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, ADMINMESSAGE_COMMAND){
	_tmp = new AdminMessage( string(ADMINMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, INFOMESSAGE_COMMAND){
	_tmp = new InfoMessage( string(INFOMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, NOTICEMESSAGE_COMMAND){
	_tmp = new NoticeMessage( string(NOTICEMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, WHOMESSAGE_COMMAND){
	_tmp = new WhoMessage( string(WHOMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, WHOISMESSAGE_COMMAND){
	_tmp = new WhoisMessage( string(WHOISMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, WHOWASMESSAGE_COMMAND){
	_tmp = new WhowasMessge( string(WHOWASMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, PONGMESSAGE_COMMAND){
	_tmp = new PongMessage( string(PONGMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, PINGMESSAGE_COMMAND){
	_tmp = new PingMessage( string(PINGMESSAGE_COMMAND) + _rawNoCmd );
	
    }else if(_skaar->isAliasFor(_command, AWAYMESSAGE_COMMAND){
	_tmp = new AwayMessage( string(AWAYMESSAGE_COMMAND) + _rawNoCmd );
    }
    
    _translation = _tmp;
    return _translation;
}
