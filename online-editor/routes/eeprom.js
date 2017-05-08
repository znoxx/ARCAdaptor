var engine = require('./lib/engine.js');
var express = require('express');
var router = express.Router();

/* GET redirects to root */
router.get('/', function(req, res, next) {
  //res.send('respond with a resource');
  res.redirect('/');
});
/* POST handler generates file */ 
router.post('/', function(req, res, next) {

  var output = engine.generateHex(req.body);
  res.setHeader('Content-Disposition', 'attachment; filename=arcadaptor8.eep');
  res.setHeader('Content-type', 'application/octet-stream');
  res.setHeader('Content-Description','File to download')
  res.charset = 'UTF-8';
  res.write(output.toString());
  res.end();
});


module.exports = router;
