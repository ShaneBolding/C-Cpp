#ifndef PARAM_
#define PARAM_

#define MAXARGS 30

class Param { 
  private:      
	long int _number; 
	char* _inputRedirect;          // file name or NULL                                                            
	char* _outputRedirect;          // file name or NULL
	int   _threads;                	      
	int   _argumentCount;           // number of tokens in argument vector       
	char* _argumentVector[MAXARGS]; // array of strings                    
	bool  _nolock;
  public:
   //CONSTRUCTORS///////////////////////////////////////////////////
   Param ();
   Param (long int N, int threads);
   
   //SETTERS////////////////////////////////////////////////////////
   void setInputRedirect(char *inputRedirect);
   void setOutputRedirect(char *outputRedirect);
   void setNumber (long int N);
   void setThreads (int T);
   void addArgument(char *argument);
   void setNolock(void);


   //DEBUGGING//////////////////////////////////////////////////////
   void printParams();
   
   //GETTERS////////////////////////////////////////////////////////
   char* getInputRedirect();
   char* getOutputRedirect();
   long int getNumber (void);
   int	 getThreads (void);
   char* getArgument(int i);
   char** getArgV(void);
   
   //PRINTERS///////////////////////////////////////////////////////
   void  printFile();
   void  grep();
   
   //FLAGS//////////////////////////////////////////////////////////
   bool  isLock(void);
   bool  isPrintDir(void);
   bool  isPrintGrep(void);
   bool  isPrintFile(void);
};

#endif
