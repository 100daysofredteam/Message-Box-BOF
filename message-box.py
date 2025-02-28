from havoc import Demon, RegisterCommand


def message_box( demonID, *params ):
    TaskID : str    = None
    demon  : Demon  = None
    # create an instance of the argument packer
    packer = Packer()
    # get an instance of the demon
    demon  = Demon(demonID)
    
    # create a task ID  
    TaskID = demon.ConsoleWrite( demon.CONSOLE_TASK, f"Tasked demon to execute Message Box BOF with message: Thank you for joining 100 Days of Red Team." )

    # instruct Havoc to run a BOF with certain parameters
    demon.InlineExecute( TaskID, "go", f"message-box.o", packer.getbuffer(), False )

    # return the new task ID
    return TaskID

def message_box2( demonID, *params ):
    TaskID : str    = None
    demon  : Demon  = None
    # create an instance of the argument packer
    packer = Packer()
    # get an instance of the demon
    demon  = Demon(demonID)
    message = ""

    if len(params) < 1:
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify a message." )
        return False
    else:
        message = params[0]


    # pack the parameters
    packer.addstr( message )
    
    # create a task ID  
    TaskID = demon.ConsoleWrite( demon.CONSOLE_TASK, f"Tasked demon to execute Message Box BOF with message: {message}" )

    # instruct Havoc to run a BOF with certain parameters
    demon.InlineExecute( TaskID, "go", f"message-box2.o", packer.getbuffer(), False )

    # return the new task ID
    return TaskID
    
RegisterCommand( message_box, "", "message-box", "Launches a message box on target machine.", 0, "Usage: message-box", "Example: message-box" )
RegisterCommand( message_box2, "", "message-box2", "Launches a message box on target machine with a custom message.", 0, "Usage: message-box2 \"<message>\"", "Example: message-box2 \"100 Days of Red Team\"" )
