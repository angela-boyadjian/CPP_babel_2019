# Binary protocols

This documentation describe the different protocols used in babel. The first part concern the communication between the server and the client. The second part is about the voice protocol between two clients.

## Protocol server <-> client

This part describe the protocol used to communicate between the server and the client.

The communication is done throught __tcp socket__.

### Packets

All packets are formated the same way, it contains a header with the __type of the request__, basically an int. This type act also as a magic number, indeed if the type is unknown the packet is corrupted.

The second part of the packet size is define by an __union of all possible request structure__. A request structure is a structure that contain mandatory and useful information about the request.
All of these structure are define in `Request.hpp`.

### Associated structure by type

Here is a list of the associated structure by type. It define wich structure is used to hold the request data.

| Type | Structure |
| -- | :------- |
| CLIENT_REGISTER | ClientInfos |
| CLIENT_CONNECT | ClientInfos |
| ADD_FRIEND | Friend |
| MESSAGE | Message |
| CALL_REQUEST | CallInfos |
| CALL_ACCEPT | CallInfos |
| CALL_DENY | CallInfos |
| HANG_UP | CallInfos |
| FRIEND_INFO | Friend |
| FRIENDS_LIST | x |
| REMOVE_FRIEND | Friend |
| GET_CLIENT_FROM_NAME | FriendAutoComplete |
| UDP_PUNCH | PortIp |

### Request class

In `Request.hpp` you have a `Request` class. This class aim to simplify this protocol, you just need to read in this class or send this class to ensure  that you read the right side and that your packet is well formated.
This class is composed of a field `type` wich is the type of the request and a field `data` wich is the union of all request structure.

## Voice ip protocol client <-> client

This part describe the protocol used to communcate voice data from a client to an other client.

This communication is done throught __udp socket__.

### Initialisation

The first part is an [udp punch](https://en.wikipedia.org/wiki/UDP_hole_punching) thanks to the server. Udp punch allow to retrives the external ip and port of the client.

> It's recommanded to read Request class section to understands the udp punch steps

Here are the steps the client have to do:
- Create udp socket
- send a `Request` to the server with type `UDP_PUNCH`
- read the `Request` result from the server.
- Verify that the `Request` type is `UDP_PUNCH`. If not restart the process
- Read in `data.network` the ip and port. It's the client __external ip and port__.
- Exchange external ip and port with the other client thanks to an other protocol.
- Reconfigure the socket to target ip and port the the other client

The client is know well configured and ready to send audio

### Data creation

The data is an audio stream encoded with a frame size of 480 (_`FRAME_SIZE` define in `Audio.hpp`_).

### Send audio

Each client send continuously audio packet.
An audio packet is formated by:
- An header defining the size encoded data.
- The data, an array of unsigned int

The size of this packet is constant, it's `sizeof(Audio::AudioPacket)` define in `Audio.hpp`