include "console.iol"
include "ui/ui.iol"
include "ui/swing_ui.iol"
include "interface.iol"

outputPort BankService {
	Location: "socket://localhost:2000"
	Protocol: sodep
	Interfaces: BankInterface
}

main
{
	showInputDialog@SwingUI( "Insert your name" )( request.name );

	keepRunning = true;

	login@BankService( request )( response );

	opMessage.sid = response.sid;
	mySid = response.sid;
	println@Console( "Server Responded: " + response.message + "\t sid: "+opMessage.sid )();

	while( keepRunning ){
		showInputDialog@SwingUI( "Insert operation type (deposit, withdraw, report, logout)" )( opMessage.message )
		
		
		if( opMessage.message == "deposit")
		{
			showInputDialog@SwingUI( "How much to deposit?" )( amountToDeposit )
			deposit.sid = mySid
			deposit.amount = int(amountToDeposit)
			deposit@BankService( deposit )( response )
			println@Console( "Server Responded: " + response.message + "\t sid: "+response.sid )()
		} 

		if( opMessage.message == "withdraw")
		{
			showInputDialog@SwingUI( "How much to withdraw?" )( amountToWithdraw )
			withdraw.sid = mySid
			withdraw.amount = int(amountToWithdraw)
			withdraw@BankService( withdraw )( response )
			println@Console( "Server Responded: " + response.message + "\t sid: "+response.sid )()
		}

		if( opMessage.message == "report")
		{
			report.sid = mySid
			report@BankService( report )( response )
			println@Console( "Server Responded: " + response.message + "\t sid: "+response.sid )()
		}
		
		if( opMessage.message == "logout")
		{
			logout.sid = mySid
			logout@BankService( logout )( response )
			println@Console( "Server Responded: " + response.message + "\t sid: "+response.sid )()
			keepRunning = false
		}
	}
}