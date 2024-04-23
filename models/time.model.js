const mongoose = require('mongoose');

const TimeSchema = mongoose.Schema(
    {
        username: {
            type: String,
            required: true,
        },
        project: {
            type: String,
            required: true,
        },
        clockin: {
            type: Array,
            required: true,
        },
        clockout: {
            type: Array,
            required: false,
        },
    }
);

const Time = mongoose.model("Time", TimeSchema);
module.exports = Time;

