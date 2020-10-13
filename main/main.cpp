#include "global.h"
#include "nodeid.h"

extern "C" void app_main()
{
    Serial.begin(115200);
    while(!Serial);
    init_nvs();
    
    // set Node ID
    set_nodeid(NODEID);

    // get Node ID
    Serial.print("Node ID get: ");
    Serial.println(get_nodeid());
}