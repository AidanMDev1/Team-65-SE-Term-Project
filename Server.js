import { WebSocketServer } from "ws";

const server = new WebSocketServer({ port: 8080 });

server.on("connection", function connection(server) {
  server.on("message", function message(data) {
    console.log("received: %s", data);
  });
  server.send("something");
});
