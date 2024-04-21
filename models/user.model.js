<<<<<<< HEAD
const mongoose = require('mongoose');

const UserSchema = mongoose.Schema(
    {
        username: {
            type: String,
            required: true
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
        }
    },
    {
        timestamps: true,
    }
);

const User = mongoose.model("User", UserSchema);
module.exports = User;
=======
const mongoose = require('mongoose');

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
        }
    },
);

const User = mongoose.model("User", UserSchema);
module.exports = User;
>>>>>>> f451d261dc4ed7d6d6e4d9f09f5ce8ceaa374ad7
