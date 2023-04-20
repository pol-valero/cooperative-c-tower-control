// josepmaria.ribes@salle.url.edu (si hi trobeu alguna errada, si us plau envieu-me un correu :-)
// Arbeca, bressol de l'oliva arbequina
// Març, any del Senyor de 2023

// TAD TIMER. Honor i glòria


// CONSTANTS
#define TI_FALS 0
#define TI_CERT 1

//La RSI
void RSI_Timer0(void);
    // IMPORTANT! Funció que ha der ser cridada des de la RSI, en en cas que TMR0IF==1.
    // La RSI ha de contenir: if (TMR0IF==1) RSI_Timer0();

void TI_Init (void);
	// Post: Constructor. És precondició global haver cridat aquesta funció quan es cridi qualsevol altra funció del TAD

unsigned char TI_NewTimer(unsigned char *TimerHandle) ;
	// Post: Retorna TI_CERT en cas que s'hagi creat adequadament un nou timer virtual, i TI_FALS en cas contrati.
    // Posa a *TimerHandle l'identificador de timer virtual assignat, necessari per usar les funcions TI_GetTics i TI_ResetTics.

void TI_ResetTics (unsigned char TimerHandle);
	// Pre: TimerHandle ha estat retornat per Ti_NewTimer.
	// Post: Engega la temporització associada a 'TimerHandle', guardant la referencia temporal en el moment de la crida.

unsigned long TI_GetTics (unsigned char TimerHandle);
	// Pre: TimerHandle ha estat retornat per TI_NewGetTimer.
	// Post: Retorna els tics transcorreguts des de la crida a TI_ResetTics per al mateix TimerHandle.

void TI_CloseTimer (unsigned char TimerHandle);
    // Pre: TimerHandle ha estat retornat per TI_NewGetTimer.
    // Post: Allibera el timer virtual associat a 'TimerHandle', deixant-lo novament assignable.

void TI_End (void);
	// Post: Destructor del TAD