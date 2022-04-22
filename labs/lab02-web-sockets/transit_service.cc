#include <map>
#include "WebServer.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View Controller Pattern
class IController {
public:
    virtual ~IController() {}
    /// Allows messages to be passed back to the view
    virtual void SendEventToView(const std::string& event, const JsonObject& details) = 0;

};

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate with the controller.
class SimulationModel {
public:
    SimulationModel(IController& controller) : controller(controller) {}

    /// Creates an simulation entity
    void CreateEntity(JsonObject& entity) {
        int id = entity["entityId"];
        std::string type = entity["type"];
        std::string name = entity["name"];
        JsonArray position = entity["position"];
        std::cout << name << ": " << position << std::endl;
    }

    /// Schedules a trip for an object in the scene
    void ScheduleTrip(JsonObject& details) {
        std::string name = details["name"];
        JsonArray start = details["start"];
        JsonArray end = details["end"];
        std::cout << name << ": " << start << " --> " << end << std::endl;
        double startx = start[0];
        double starty = start[1];
        double endx = start[0];
        double endy = start[1];
        controller.SendEventToView("TripScheduled", details);
    }

    /// Updates the simulation
    void Update(double dt) {
    }

private:
    IController& controller;
};


//--------------------  Controller ----------------------------

/// A Transit Service that communicates with a web page through web sockets.  It also acts as the controller
/// in the model view controller pattern.
class TransitService : public JsonSession, public IController {
public:
    TransitService(SimulationModel& model) : model(model) {}

    /// Handles specific commands from the web server
    void ReceiveCommand(const std::string& cmd, JsonObject& data, JsonObject& returnValue) {
        std::cout << cmd << ": " << data << std::endl;
        if (cmd == "CreateEntity") {
            model.CreateEntity(data);
        }
        else if (cmd == "ScheduleTrip") {
            model.ScheduleTrip(data);
        }
        else if (cmd == "ping") {
            returnValue["response"] = data;
        }
    }

    /// Allows messages to be passed back to the view
    void SendEventToView(const std::string& event, const JsonObject& details) {
        picojson::object e;
        JsonObject eventData(e);
        eventData["event"] = event;
        eventData["details"] = details;
        sendMessage(eventData.ToString());
    }

private:
    SimulationModel& model;
};


//--------------------  View / Web Server Code ----------------------------

/// The TransitWebServer holds the simulation and updates sessions.
class TransitWebServer : public WebServerBase, public IController {
public:
	TransitWebServer(int port = 8081, const std::string& webDir = ".") : WebServerBase(port, webDir), model(*this) {}
    void SendEventToView(const std::string& event, const JsonObject& details) {
        for (int i = 0; i < sessions.size(); i++) {
            static_cast<TransitService*>(sessions[i])->SendEventToView(event, details);
        }
    }
protected:
	Session* createSession() { return new TransitService(model); }
private:
    SimulationModel model;
};

/// The main program that handels starting the web sockets service.
int main(int argc, char**argv) {
    if (argc > 1) {
        int port = std::atoi(argv[1]);
        std::string webDir = std::string(argv[2]);
        TransitWebServer server(port, webDir);
        while (true) {
            server.service();
        }
    }
    else {
        std::cout << "Usage: ./build/WebApp 8081 web" << std::endl;
    }

    return 0;
}

