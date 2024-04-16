const express = require('express');
const mongoose = require('mongoose');
const User = require('./models/user.model.js');
const Timetable = require('./models/timetable.model.js');
const Announcement = require('./models/announcement.model.js');
const app = express();

app.use(express.json());

app.get('/', (req,res) => {
    res.send("hello from the node.js");
});

app.get('/api/allusers', async (req,res) => {
    try {
        const users = await User.find({});
        res.status(200).json(users); 
    } catch (error) {
        res.status(500).json({message: error.message});     
    }
});

app.get('/api/finduser/:user/:pass', async (req,res) => {
    try {
        const {user, pass} = req.params;
        const finduser = await User.find({username: user, password: pass});
        res.status(200).json(finduser);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
})

app.post('/api/userpost', async (req,res) => {
    try {
        const user = await User.create(req.body);
        res.status(200).json(user);
    } 
    catch (error) {
        res.status(500).json({message: error.message});          
    }
});

mongoose.connect("mongodb+srv://Team65:ka1o40V2jAj4SstC@questclock.ofavxyx.mongodb.net/QuestClockLogin?retryWrites=true&w=majority&appName=QuestClock")
.then(() => {
    console.log("connected to database");
    app.listen(8000, () => {
        console.log("Server is running on port 8000");
    });
})
.catch(() => {
    console.log("connection failed");
});