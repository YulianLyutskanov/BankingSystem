# Banking System

Course project Banking System, created by me for my Object Oriented Programming - Practicum course @ FMI, Sofia University.

This banking system implements essential banking functionalities and supports multiple types of users.

## User Roles

1. **Client** - A regular user who owns accounts in different banks.
2. **Bank Employee** - Handles user requests such as account creation, closure, and transfers.
3. **Third-party Employee** - Issues checks for bank clients.

## Commands and Functionalities

### Client Commands
- `check_avl [bank_name] [account_number]` - Displays the balance of the specified account.
- `open [bank_name]` - Requests the opening of a new account in the specified bank.
- `close [bank_name] [account_number]` - Requests to close an account.
- `redeem [bank_name] [account_number] [verification_code]` - Deposits a check into the specified account.
- `change [new_bank_name] [current_bank_name] [account_number]` - Requests account transfer to another bank.
- `list [bank_name]` - Lists all accounts owned by the user in the specified bank.
- `messages` - Displays messages received from the bank.

### Bank Employee Commands
- `tasks` - Lists pending tasks assigned to the employee.
- `view [task_id]` - Shows details of a task.
- `approve [task_id]` - Approves a request.
- `disapprove [task_id] [message]` - Rejects a request with a message.
- `validate [task_id]` - Validates a user's information before transferring an account.

### Third-party Employee Commands
- `send_check [sum] [verification_code] [egn]` - Issues a check for a user.

### General Commands (For All Users)
- `exit` - Logs out from the system.
- `whoami` - Displays user information.
- `help` - Shows a list of available commands.

### System Commands
- `login` - Logs a user into the system.
- `signup` - Registers a new user with a specific role.
- `create_bank` - Creates a new bank (no account required).

## System Requirements
- The system must persist data between sessions.
- All transactions and operations should be properly logged.


View example usages in the pdf description file above.


