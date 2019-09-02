const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const {PORT, DEV_LOCATION} = require('./config');

const app = express();

var hbs = require('express-handlebars');
var viewsPath = path.join(__dirname, '/public/views');
app.set('views', viewsPath);
app.engine('handlebars', hbs({
    defaultLayout: 'main',
    layoutsDir: `${viewsPath}/layouts`,
    partialsDir: `${viewsPath}/partials`
}));
app.set('view engine', 'handlebars');

var options = {
    dotfiles: 'ignore',
    etag: false,
    extensions: ['htm', 'html'],
    index: false
};

app.use(express.static(path.join(__dirname, 'public') , options));

app.use(bodyParser.json());

app.get('/', (req, res) => {
    // Display the splash screen
    res.render('splash_screen', { api_location: DEV_LOCATION });
});

app.get('/instructions', (req, res) => {
    res.render('instructions', { api_location: DEV_LOCATION });
});

app.get('/options', (req, res) => {
    res.render('options', { api_location: DEV_LOCATION });
});

app.get('/highscores', (req, res) => {
    if(req.query == undefined || req.query.score == undefined) {
        res.redirect('/options');
    } else {
        res.render('highscores', { api_location: DEV_LOCATION });
    }
});

app.get('/game', (req, res) => {
    if(req.query == undefined || req.query.pancakeOrder == undefined || req.query.difficulty == undefined) {
        res.redirect('/options');
    } else {
        res.render('game', { api_location: DEV_LOCATION });
    }
});

app.get('/gameover', (req, res) => {
    if(req.query == undefined || req.query.result == undefined || req.query.score == undefined) {
        res.redirect('/options');
    } else {
        res.render('gameover', { api_location: DEV_LOCATION });
    }
});

app.listen(process.env.PORT || 3000)
