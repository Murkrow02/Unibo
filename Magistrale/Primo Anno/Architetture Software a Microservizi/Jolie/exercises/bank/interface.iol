type LoginRequest: void {
	.name: string
}

type LogoutRequest: void {
	.sid: string
}

type WithdrawRequest: void{
	.sid: string
	.amount: int
}

type DepositRequest: void{
	.sid: string
	.amount: int
}

type ReportRequest: void{
	.sid: string
}

type LoginResponse {
	.sid: string
	.message: string
}
type Response {
	.message: string
}

interface BankInterface {
	RequestResponse: login(LoginRequest)(LoginResponse), deposit(DepositRequest)(Response), withdraw(WithdrawRequest)(Response), report(ReportRequest)(Response),logout(LogoutRequest)(Response)
}