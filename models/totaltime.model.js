const mongoose = require('mongoose');

const TotaltimeSchema = mongoose.Schema(
    {
        username: {
            type: String,
            required: true,
        },
        time_worked: {
            type: String,
            required: true,
        }
    }
);

const Totaltime = mongoose.model("Totaltime", TotaltimeSchema);
module.exports = Totaltime;