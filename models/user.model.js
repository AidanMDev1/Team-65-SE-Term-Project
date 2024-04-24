const mongoose = require('mongoose');
const Time = require('./time.model');

const UserSchema = mongoose.Schema(
    {
        username: {
            type: String,
            required: true,
            unique: true
        },
        password: {
            type: String,
            required: true
        },
        role: {
            type: String,
            required: true
        },
        projects: {
            type: Array,
            required: true
        },
    }
);

const User = mongoose.model("User", UserSchema);
module.exports = User;