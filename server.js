const express = require('express');
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');
const User = require('./models/user.model.js');
const Time = require('./models/time.model.js');
const Totaltime = require('./models/totaltime.model.js');
const Notification = require('./models/notification.model.js');
const Project = require('./models/project.models.js');

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

//functionality to check if a timetable exists
app.get('/api/check_time/:user/:proj', async (req,res) =>{
    try {
        const { user, proj } = req.params;
        const check_time = await Time.findOne({username: user, project: proj});
        res.status(200).json(check_time);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
});

//functionality for project clock in if it doesnt exist
app.get('/api/create_clockin/:user/:proj', async (req,res) => {
    try {
        const { user, proj } = req.params;
        const time = new Date().toLocaleDateString([], {hour:'2-digit', minute:'2-digit'});
        const create_clockin = await Time.create({username: user, project: proj, clockin: [time]});
        res.status(200).json(create_clockin);
    } catch (error) {
        res.status(500).json({message: error.message});  
    }
})

//functionality for project clock in if it does exist
app.get('/api/clockin/:user/:proj', async (req,res) => {
    try {
        const { user, proj } = req.params;
        const time = new Date().toLocaleDateString([], {hour:'2-digit', minute:'2-digit'});
        const clock_in = await Time.findOneAndUpdate({username: user, project: proj}, {$push: {clockin: time}});
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
        const clock_out = await Time.findOneAndUpdate({username: user, project: proj}, {$push: {clockout: time}});
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
app.get('/api/send_notification/:user/:from/:notif', async (req,res) => {
    try {
        const { user, from, notif } = req.params;
        const notify = await Notification.create({username: user, sender: from, notification: notif});
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
        const { user, pass, pos, proj1 } = req.params;
        const createuser = await User.create({username: user, password: pass, role: pos, projects: [proj1]});
        res.status(200).json(createuser);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality to check if a user exists in db
app.get('/api/check_user/:user', async (req,res) => {
    try {
        const { user } = req.params;
        const check_user = await User.findOne({username: user});
        res.status(200).json(check_user);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality to check if a user has a given project
app.get('/api/check_user_project/:user/:proj', async (req,res) => {
    try {
        const { user, proj} = req.params;
        const check_user_project = await User.findOne({username: user, projects: proj});
        res.status(200).json(check_user_project);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality for admins to assign projects to users
app.get('/api/assign_user/:user/:proj', async (req,res) => {
    try {
        const { user, proj } = req.params;
        const assign_user = await User.findOneAndUpdate({username: user}, {$push: {projects: proj}});
        res.status(200).json(assign_user);
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

//functionality to create projects
app.get('/api/create_project/:proj/:manager/:cli', async (req, res) => {
    try {
        const { proj, manager, cli } = req.params;
        const create_project = await Project.create({project_name: proj, project_manager: manager, client: cli});
        res.status(200).json(create_project);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality to edit a project's manager and client
app.get('/api/edit_project/:proj/:manager/:cli', async (req, res) => {
    try {
        const { proj, manager, cli } = req.params;
        const edit_project = await Project.findOneAndUpdate({project_name: proj}, {project_manager: manager, client: cli});
        res.status(200).json(edit_project);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality to check if a certain project exists
app.get('/api/check_project/:proj', async (req, res) => {
    try {
        const { proj } = req.params;
        const check_project = await Project.findOne({project_name: proj});
        res.status(200).json(check_project);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});

//functionality to get info about project
app.get('/api/get_project_info/:proj', async (req, res) => {
    try {
        const { proj } = req.params;
        const get_project_info = await Project.findOne({project_name: proj});
        res.status(200).json(get_project_info);
    } catch (error) {
        res.status(500).json({message: error.message}); 
    }
});


//functionality to get all projects under a given manager
app.get('/api/manager_projects/:manager', async (req, res) => {
    try {
        const { manager } = req.params;
        const manager_projects = await Project.find({project_manager: manager});
        res.status(200).json(manager_projects);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality to find user given project
app.get('/api/project_members/:proj', async (req, res) => {
    try {
        const { proj } = req.params;
        const project_members = await User.find({projects: proj});
        res.status(200).json(project_members);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality to find all user clockin times for a given project
app.get('/api/get_clockin/:user/:proj', async (req, res) => {
    try {
        const { user, proj } = req.params;
        const get_clockin = await Time.find({username: user, project: proj});
        res.status(200).json(get_clockin);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality to find all user clockout times for a given project
app.get('/api/get_clockout/:user/:proj', async (req, res) => {
    try {
        const { user, proj } = req.params;
        const get_clockout = await Time.find({username: user, project: proj});
        res.status(200).json(get_clockout);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality for creating a total time tracker for a user
app.get('/api/total_time_create/:user', async (req, res) => {
    try {
        const { user } = req.params;
        const total_time_create = await Totaltime.create({username: user, time_worked: "0", times_clockin: "0"});
        res.status(200).json(total_time_create);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

// functionality to update total time
app.get('/api/total_time_update/:user/:time/:clockin', async (req, res) => {
    try {
        const { user, time, clockin } = req.params;
        const total_time_update = await Totaltime.findOneAndUpdate({username: user}, {time_worked: time, times_clockin: clockin});
        res.status(200).json(total_time_update);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality to get totaltime
app.get('/api/get_total_time/:user', async (req, res) => {
    try {
        const { user } = req.params;
        const get_total_time = await Totaltime.findOne({username: user});
        res.status(200).json(get_total_time);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality to get user notifications
app.get('/api/get_notifications/:user', async (req, res) => {
    try {
        const { user } = req.params;
        const get_notifications = await Notification.find({username: user});
        res.status(200).json(get_notifications);
    } catch (error) {
        res.status(500).json({message: error.message});
    }
});

//functionality to get notification sender
app.get('/api/get_sender/:user', async (req, res) => {
    try {
        const { user } = req.params;
        const get_sender = await Notification.find({username: user});
        res.status(200).json(get_sender);
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