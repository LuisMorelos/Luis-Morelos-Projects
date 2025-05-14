const http = require("http");
const fs = require("fs");

const port = 3456;
const file = "client.html";

// Chat room data structure
const chatRooms = {};
const bannedUsers = {}; // { roomName: { username: true } }
const userSockets = {}; // { username: socketId }

// Create HTTP server
const server = http.createServer(function(req, res) {
    fs.readFile(file, function(err, data) {
        if (err) return res.writeHead(500);
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(data);
    });
});

// Import Socket.IO and pass our HTTP server object to it.
const socketio = require("socket.io")(http, {
    wsEngine: 'ws'
});

// Attach our Socket.IO server to our HTTP server to listen
const io = socketio.listen(server);

io.sockets.on("connection", function(socket) {
    console.log("New user connected");
    
    let currentUser = null;
    let currentRoom = null;
    
    // Handle user joining
    socket.on('join', function(data) {
        const { username, roomName, password } = data;
        
        // Check if user is banned from this room
        if (bannedUsers[roomName] && bannedUsers[roomName][username]) {
            socket.emit('error', { message: 'You are banned from this room' });
            return;
        }
        
        // Check if room exists and password matches (for private rooms)
        if (chatRooms[roomName] && chatRooms[roomName].isPrivate) {
            if (chatRooms[roomName].password !== password) {
                socket.emit('error', { message: 'Incorrect password' });
                return;
            }
        }
        
        // Create room if it doesn't exist
        if (!chatRooms[roomName]) {
            chatRooms[roomName] = {
                users: {},
                isPrivate: !!password,
                password: password || null,
                creator: username
            };
        }
        
        // Add user to room
        chatRooms[roomName].users[username] = socket.id;
        userSockets[username] = socket.id;
        currentUser = username;
        currentRoom = roomName;
        
        // Notify room
        io.to(roomName).emit('user_joined', { 
            username,
            users: Object.keys(chatRooms[roomName].users)
        });
        
        // Join the room channel
        socket.join(roomName);
        
        // Send success to user
        socket.emit('joined', { 
            roomName, 
            users: Object.keys(chatRooms[roomName].users),
            isCreator: chatRooms[roomName].creator === username
        });
    });
    //bad word filter
    const badWords = ["fuck","shit","crap","damn","neecrob"];
    function censorMessage(message) {
    	const regex = new RegExp(`\\b(${badWords.join("|")})\\b`, "gi");
    	return message.replace(regex, (match) => "*".repeat(match.length));
	}
    // Handle public messages
    socket.on('message_to_server', function(data) {
        if (!currentRoom || !currentUser) return;
        const cleanMessage = censorMessage(data.message);
        const message = {
            text: cleanMessage,
            from: currentUser,
            timestamp: new Date().toISOString(),
            isPrivate: false
        };
        
        io.to(currentRoom).emit('message_to_client', message);
    });
    
    // Handle private messages
    socket.on('private_message', function(data) {
        if (!currentRoom || !currentUser) return;
        
        const recipientSocketId = chatRooms[currentRoom].users[data.to];
        if (!recipientSocketId) {
            socket.emit('error', { message: 'User not found in room' });
            return;
        }
        const cleanMessage = censorMessage(data.message);
        const message = {
            text: cleanMessage,
            from: currentUser,
            to: data.to,
            timestamp: new Date().toISOString(),
            isPrivate: true
        };
        
        // Send to recipient
        io.to(recipientSocketId).emit('private_message', message);
        // Send copy to sender
        socket.emit('private_message', message);
    });
    
    // Handle kicking users
    socket.on('kick_user', function(data) {
        if (!currentRoom || !currentUser) return;
        
        const room = chatRooms[currentRoom];
        if (room.creator !== currentUser) {
            socket.emit('error', { message: 'Only room creator can kick users' });
            return;
        }
        
        const userToKick = data.username;
        if (!room.users[userToKick]) {
            socket.emit('error', { message: 'User not in room' });
            return;
        }
        
        const kickSocketId = room.users[userToKick];
        delete room.users[userToKick];
        
        // Notify kicked user
        io.to(kickSocketId).emit('kicked', { roomName: currentRoom });
        // Notify room
        io.to(currentRoom).emit('user_left', { 
            username: userToKick,
            users: Object.keys(room.users)
        });
    });
    
    // Handle banning users
    socket.on('ban_user', function(data) {
        if (!currentRoom || !currentUser) return;
        
        const room = chatRooms[currentRoom];
        if (room.creator !== currentUser) {
            socket.emit('error', { message: 'Only room creator can ban users' });
            return;
        }
        
        const userToBan = data.username;
        if (!room.users[userToBan]) {
            socket.emit('error', { message: 'User not in room' });
            return;
        }
        
        // Add to banned list
        if (!bannedUsers[currentRoom]) {
            bannedUsers[currentRoom] = {};
        }
        bannedUsers[currentRoom][userToBan] = true;
        
        const banSocketId = room.users[userToBan];
        delete room.users[userToBan];
        
        // Notify banned user
        io.to(banSocketId).emit('banned', { roomName: currentRoom });
        // Notify room
        io.to(currentRoom).emit('user_left', { 
            username: userToBan,
            users: Object.keys(room.users)
        });
    });
    
    // Handle disconnection
    socket.on('disconnect', function() {
        if (!currentRoom || !currentUser) return;
        
        const room = chatRooms[currentRoom];
        if (room && room.users[currentUser]) {
            delete room.users[currentUser];
            delete userSockets[currentUser];
            
            // Notify room if still connected
            io.to(currentRoom).emit('user_left', { 
                username: currentUser,
                users: Object.keys(room.users)
            });
            
            // Delete room if empty
            if (Object.keys(room.users).length === 0) {
                delete chatRooms[currentRoom];
            }
        }
    });
});

server.listen(port, function() {
    console.log(`Server running on port ${port}`);
});
