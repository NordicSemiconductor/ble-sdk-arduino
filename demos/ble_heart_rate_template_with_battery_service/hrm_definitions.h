#define NO_DATA 255

//Return values for heart rate data buffer operations
typedef enum {SUCCESS, BUFFER_EMPTY, BUFFER_FULL} buffer_operation_status_code_t;
	
typedef enum {SIMULATION, MEASUREMENT} data_source_t;