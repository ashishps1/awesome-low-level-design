using System;
using System.Collections.Generic;
using System.Threading;

public class ATMDemo
{
    public static void Main(string[] args)
    {
        ATM atm = ATM.GetInstance();

        // Perform Check Balance operation
        atm.InsertCard("1234-5678-9012-3456");
        atm.EnterPin("1234");
        atm.SelectOperation(OperationType.CHECK_BALANCE); // $1000

        // Perform Withdraw Cash operation
        atm.InsertCard("1234-5678-9012-3456");
        atm.EnterPin("1234");
        atm.SelectOperation(OperationType.WITHDRAW_CASH, 570);

        // Perform Deposit Cash operation
        atm.InsertCard("1234-5678-9012-3456");
        atm.EnterPin("1234");
        atm.SelectOperation(OperationType.DEPOSIT_CASH, 200);

        // Perform Check Balance operation
        atm.InsertCard("1234-5678-9012-3456");
        atm.EnterPin("1234");
        atm.SelectOperation(OperationType.CHECK_BALANCE); // $630

        // Perform Withdraw Cash more than balance
        atm.InsertCard("1234-5678-9012-3456");
        atm.EnterPin("1234");
        atm.SelectOperation(OperationType.WITHDRAW_CASH, 700); // Insufficient balance

        // Insert Incorrect PIN
        atm.InsertCard("1234-5678-9012-3456");
        atm.EnterPin("3425");
    }
}