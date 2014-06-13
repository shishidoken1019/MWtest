 <?php
 // MW config
 require_once('C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MW\mw.conf');
 
 // config
 $bp = 'C:\03_shishido\shishido_program_file2.0\php\include\MW';
 $config = $bp . 'config.conf';

 
 //
 require_once('C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MW\controller.inc');
 
   //
   $cobj = new controller;
  // $cobj->set_base_path($bp);
   $cobj->set_config($config);
   $cobj->run();