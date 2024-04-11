const mongoose = require('mongoose');

const AnnouncementSchema = mongoose.Schema(
    {
        username: {
            type: String,
            require: true
        },
        announcement: {
            type: String,
            require: true
        },
    }
);

const Announcement = mongoose.model("Announcement", AnnouncementSchema);
module.exports = Announcement;