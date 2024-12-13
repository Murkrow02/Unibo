include "console.iol"
include "interface.iol"

inputPort BankService {
	Location: "socket://localhost:2000"
	Protocol: sodep
	Interfaces: BankInterface
}

cset {
	sid: LogoutRequest.sid DepositRequest.sid WithdrawRequest.sid ReportRequest.sid
}

execution{ concurrent }

init {
	keepRunning = true
}

main
{
    
	login( request )( response ){
		username = request.name;
		response.sid = csets.sid = new;
		response.message = "You are logged in."
		println@Console("User "+username+" logged in.")()
	};

	balance = 0

	while( keepRunning ){
		[ logout( request )(response) ] { 
			println@Console("User "+username+" logged out.")();
			keepRunning = false }

		[ deposit( request )(response) 
			{ 
			println@Console("Request to deposit.")()
			balance = balance + request.amount
			response.message = "New balance: "+balance
			}
		] {
			println@Console("Updated user balance to "+balance)()
		}

			[ withdraw( request )(response) 
			{
			println@Console("Request to withdraw.")()
			balance = balance - request.amount
			response.message = "New balance: "+balance
			}
		] {
			println@Console("Updated user balance to "+balance)()
		}

		[ report( request )(response) 
			{
			println@Console("Request to report.")()
			response.message = "Current balance: "+balance
			}
		] {
			println@Console("User balance is "+balance)()
		}

	}
}