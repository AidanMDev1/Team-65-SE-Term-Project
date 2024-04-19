const mongoose = require('mongoose');

const TimetableSchema = mongoose.Schema(
    {
        username: {
            type: String,
            required: true
        },
        timelogs: {
            type: Array,
            required: true
        },
    }
);

const Timetable = mongoose.model("Timetable", TimetableSchema);
module.exports = Timetable;