const mongoose = require('mongoose');

const NotificationSchema = mongoose.Schema(
    {
        username: {
            type: String,
            require: true,
        },
        notification: {
            type: String,
            require: true
        },
    }
);

const Notification = mongoose.model("Notification", NotificationSchema);
module.exports = Notification;