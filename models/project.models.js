const mongoose = require('mongoose');

const ProjectSchema = mongoose.Schema(
    {
        project_name: {
            type: String,
            required: true,
        },
        project_manager: {
            type: String,
            required: true
        },
        client: {
            type: String,
            required: true
        }
    }
);

const Project = mongoose.model("Project", ProjectSchema);
module.exports = Project;