const express = require('express');
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');
const User = require('./models/user.model.js');
const Time = require('./models/time.model.js');
const Notification = require('./models/notification.model.js');

const app = express();
app.use(bodyParser.json());
app.use(express.urlencoded({extended: false}));

app.get('/', (req,res) => {
    res.send("Welcome to Questclock");
});

//functionality to find all users within database
app.get('/api/allusers', async (req,res) => {
    try {
        const users = await User.find({});
        res.status(200).json(users); 
    } catch (error) {
        res.status(500).json({message: error.message});     
    }
});

//functionality for a user to login, searches database for an object with given username and password
app.get('/api/login/:user/:pass', async (req,res) => {
    try {
        const {user, pass} = req.params;
        const login = await User.findOne({username: user, password: pass});
        res.status(200).json(login);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
})

//functionality for clock in
app.get('/api/clockin/:user/:proj', async (req,res) => {
    try {
        const { user, proj } = req.params;
        const time = new Date().toLocaleDateString([], {hour:'2-digit', minute:'2-digit'});
        const clock_in = await Time.create({username: user, project: proj, clockin: [time]});
        res.status(200).json(clock_in);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
})

//functionality for clock out
app.get('/api/clockout/:user/:proj', async (req,res) => {
    try {
        const { user, proj } = req.params;
        const time = new Date().toLocaleDateString([], {hour:'2-digit', minute:'2-digit'});
        const clock_out = await Time.findOneAndUpdate({username: user, project: proj}, {clockout: [time]});
        res.status(200).json(clock_out);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
})

//functionality for a user to see all their notifications
app.get('/api/notifications/:user', async (req,res) => {
    try {
        const { user } = req.params;
        const notifs = await Notification.find({username: user});
        res.status(200).json(notifs);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
});

//functionality for admins and managers to notify other users
app.get('/api/send_notification/:user/:notif', async (req,res) => {
    try {
        const { user, notif } = req.params;
        const notify = await Notification.create({username: user, notification: notif});
        res.status(200).json(notify);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    };
})

//functionality for admins and managers to delete previously sent notifications
app.get('/api/delete_notification/:user/:notif', async (req, res) => {
    try {
        const { user, notif } = req.params;
        const del = await Notification.deleteOne({username: user, notification: notif});
        res.status(200).json(del);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality for admins to create new users
app.get('/api/create_user/:user/:pass/:pos/:proj1', async (req,res) => {
    try {
        const { user, pass, pos, proj1, proj2 } = req.params;
        const createuser = await User.create({username: user, password: pass, role: pos, projects: [proj1]});
        res.status(200).json(createuser);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality for admins to delete/fire users
app.get('/api/delete_user/:user', async (req, res) => {
    try {
        const { user } = req.params;
        const del = await User.deleteOne({username: user});
        res.status(200).json(del);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

mongoose.connect("mongodb+srv://Team65:ka1o40V2jAj4SstC@questclock.ofavxyx.mongodb.net/QuestClockLogin?retryWrites=true&w=majority&appName=QuestClock")
.then(() => {
    console.log("connected to database");
    app.listen(6500, () => {
        console.log("Server is running on port 6500");
    });
})
.catch(() => {
    console.log("connection failed");
});
