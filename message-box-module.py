from havoc import Demon, RegisterCommand
from pathlib import Path
    
 
def message_box3( demonID, *params ):
    TaskID : str    = None
    demon  : Demon  = None
    # create an instance of the argument packer
    packer = Packer()
    # get an instance of the demon
    demon  = Demon(demonID)
    messageType = ""
    message = ""

    if len(params) < 1:
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify a type." )
        return False
    else:
        messageType = params[0].lower()
    if params[0].lower() != "custom" and params[0].lower() != "static":
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify a vaild type." )
        return False
    
    if params[0].lower() == "custom" and len(params) < 2:
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify a message." )
        return False
    elif params[0].lower() == "custom":
        message = params[1]


    # pack the parameters
    packer.addstr( messageType )
    packer.addstr( message )
    
    # create a task ID  
    TaskID = demon.ConsoleWrite( demon.CONSOLE_TASK, f"Tasked demon to execute Message Box BOF with a {messageType} message." )

    # instruct Havoc to run a BOF with certain parameters
    demon.InlineExecute( TaskID, "go", f"message-box3.o", packer.getbuffer(), False )

    # return the new task ID
    return TaskID
    
def message_box4( demonID, *params ):
    TaskID : str    = None
    demon  : Demon  = None
    # create an instance of the argument packer
    packer = Packer()
    # get an instance of the demon
    demon  = Demon(demonID)
    messageType = ""
    fileLocation = ""
    message = ""
    filePath = ""
    if len(params) < 1:
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify the source file location (local or remote)." )
        return False
    else:
        fileLocation = params[0]
    if fileLocation.lower() != "local" and fileLocation.lower() != "remote":
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify a valid source file location (local or remote)." )
        return False
    
    if len(params) < 2:
        demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify the source file path." )
        return False
    else:
        filePath = params[1]
        
    if fileLocation.lower() == "local":
        messageType = "custom"
        try:
             with open(filePath, 'rb') as f:
                message = f.read()
        except:
            demon.ConsoleWrite( demon.CONSOLE_ERROR, f"Error: Please specify a valid file path." )
            return False

    # pack the parameters
    packer.addstr( messageType )
    packer.addstr( message )
    packer.addstr( filePath )
    
    # create a task ID  
    TaskID = demon.ConsoleWrite( demon.CONSOLE_TASK, f"Tasked demon to execute Message Box BOF with a message stored in a {fileLocation} file." )

    # instruct Havoc to run a BOF with certain parameters
    if fileLocation.lower() == "local":
        demon.InlineExecute( TaskID, "go", f"message-box3.o", packer.getbuffer(), False )
    else:
        demon.InlineExecute( TaskID, "go", f"message-box4.o", packer.getbuffer(), False )
    # return the new task ID
    return TaskID


RegisterModule( "message-box", "Message Box Demo Module", "", "[subcommand] (args)", "", ""  )
RegisterCommand( message_box3, "message-box", "msg", "Launches a message box on target machine with a custom or static message.", 0, "Usage: message-box3 <message type> \"<message (optional)>\"", "Example: message-box3 custom \"100 Days of Red Team\"" )
RegisterCommand( message_box4, "message-box", "file", "Launches a message box on target machine with a message stored in a file.", 0, "Usage: message-box4 <file location> <file path>", "Example: message-box4 local /path/to/file" )
