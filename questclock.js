const MongoClient = require('mongodb');
const mongoose = require('mongoose');

async function main()
{
    const uri = "mongodb+srv://Team65:ka1o40V2jAj4SstC@questclock.ofavxyx.mongodb.net/?retryWrites=true&w=majority&appName=QuestClock";
    const client = new MongoClient(uri);

    try 
    {
        await client.connect();
        await listDatabases(client);

    }
    catch(e) 
    {
        console.error(e);
    }
    finally 
    {
        await client.close();
    }
}

main().catch(console.error);

async function listDatabases(client) 
{
    const databasesList = await client.db().admin().listDatabases();
    console.log("Databases: ");
    databasesList.databases.forEach(db => {console.log(`- ${db.name}`);})
}
