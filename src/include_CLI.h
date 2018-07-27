/**
 * GeekFactory - "Construye tu propia tecnologia"
 * Distribucion de materiales para el desarrollo e innovacion tecnologica
 * www.geekfactory.mx
 *
 * Ejemplo de libreria Shell. Este ejemplo representa la configuracion minima
 * requerida para implementar la funcionalidad de interfaz de comandos. En esta
 * ocasion registramos 2 comandos y enviamos texto como respuesta a cada uno.
 *
 * Example for Shell library. This example shows the minimum setup needed to
 * implement a command line interface. This time we register 2 commands and we
 * send text as response for each command.
 */

#include <Shell.h>
#define CONFIG_SHELL_MAX_COMMANDS = 25;
int iStart = 0;

/**
 * Test commands: The commands should always use this function prototype.
 * They receive 2 parameters: The total count of arguments (argc) and a pointer 
 * to the begining of each one of the null-terminated argument strings.
 *
 * In this example we ignore the parameters passed to the functions
 */
int command_mycommand(int argc, char** argv)
{
  shell_println("Running \"mycommand\" now");
  shell_println("Exit...");
  return SHELL_RET_SUCCESS;
}

int command_othercommand(int argc, char** argv)
{
  shell_println("Running \"othercommand\" now");
  shell_println("Exit...");
  return SHELL_RET_SUCCESS;
}

/**
 * Function to read data from serial port
 * Functions to read from physical media should use this prototype:
 * int my_reader_function(char * data)
 */
int shell_reader(char * data)
{
  // Wrapper for Serial.read() method
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}

int command_test(int argc, char** argv)
{
  int i;

  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n",argc);

  // Print each argument with string lenghts
  for(i=0; i<argc; i++)
  {
    // Print formatted text to terminal
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]) );
  }

  return SHELL_RET_SUCCESS;
}

int command_show(int argc, char** argv){
    int i;
    if (argc < 2){
        iStart++;
        ShowEntries(getout,iStart,3);
    }

    for(i=0; i<argc; i++)
    {
        //shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]) );
    }
    i =strtol(argv[1],0,0);
    ShowEntries(getout,i,3);
    iStart = i;
    
  return SHELL_RET_SUCCESS;    
}

int command_heap(int argc, char** argv)
{
    
  shell_println(string2char((String)"Currently free RAM"));
  shell_println(string2char((String)ESP.getFreeHeap()));
  return SHELL_RET_SUCCESS;
}

int command_read(int argc, char** argv){
    shell_println(string2char( sd_getfilecontent(getout)));
  //shell_println(string2char((String)ESP.getFreeHeap()));
  return SHELL_RET_SUCCESS;  
}

int command_done(int argc, char** argv){
  shell_println(string2char( sd_getfilecontent(getout)));
  int EntryNumber =strtol(argv[1],0,0);
  UpdateDone(getout,EntryNumber,1);

  //shell_println(string2char((String)ESP.getFreeHeap()));
  return SHELL_RET_SUCCESS;  
}

int command_undone(int argc, char** argv){
  shell_println(string2char( sd_getfilecontent(getout)));
  int EntryNumber =strtol(argv[1],0,0);
  UpdateDone(getout,EntryNumber,0);

  //shell_println(string2char((String)ESP.getFreeHeap()));
  return SHELL_RET_SUCCESS;  
}

/**
 * Function to write data to serial port
 * Functions to write to physical media should use this prototype:
 * void my_writer_function(char data)
 */
void shell_writer(char data)
{
  // Wrapper for Serial.write() method
  Serial.write(data);
}

void CLI_Setup(){
    delay(1000);
    shell_init(shell_reader, shell_writer, 0);
    
    shell_register(command_mycommand, PSTR("mycommand"));
    shell_register(command_othercommand, PSTR("othercommand"));
    shell_register(command_read, PSTR("read"));
    shell_register(command_done, PSTR("done"));    
    shell_register(command_undone, PSTR("undone"));    

    shell_register(command_test, PSTR("test"));
    shell_register(command_show, PSTR("show"));
    shell_register(command_heap, PSTR("heap"));


}

void CLI_loop() {
shell_task();
}