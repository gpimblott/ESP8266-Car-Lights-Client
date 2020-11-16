#include <stdlib.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include "webpage.h"
#include "lights.h"

const char* mySSID     = "wifi";
const char* myPASSWORD = "password";

const char sep[2] = ",";

ESP8266WebServer server(80);

/***** prototype declaration *****/
void handleRoot();
void handleLights();


void setup() {

  // Debug serial
  Serial.begin(115200);

  // We only need TX for the lights so use Serial 1 and leave Serial0 for debug
  Serial1.begin(9600);

  // Start with jackpot
  Serial1.println("SEQ:JACKPOT");

  // Wait for it....then try and connect to the wifi
  delay(100);
  WiFi.disconnect();
  WiFi.begin(mySSID, myPASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print( "." );
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  Serial1.println("SEQ:REVERSE");

  // Create the webserver
  server.on("/", handleRoot);
  server.on("/lights", HTTP_POST, handleLights);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

// We don't have anything to do
void loop() {
  server.handleClient();
  yield();
}

// Dispay the home page
void handleRoot() {
  size_t n = sizeof(commands) / sizeof(commands[0]);


  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send ( 200, "text/html", pageHeader);

  server.sendContent("<form action='/lights' method='post'>");

  for ( int x = 0; x < n; x++ ) {
    String idStr = "id_" + String(x);
    server.sendContent("<input type='radio' name='sequence' id='" + idStr + "' value='" + commands[x].sequence + "'>"
                       "<label for='" + idStr + "'>" + commands[x].commandName + "</label><br>");
  }
  server.sendContent( "<input type='submit' value='Submit'>"
                      "</form>");

  server.sendContent(pageFooter);
}


//  Handle a POST with the new light sequence to set
void handleLights() {
  if ( server.hasArg("sequence")) {
    Serial1.println( server.arg("sequence") );
  }
  server.sendHeader("Location", "/");       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}
