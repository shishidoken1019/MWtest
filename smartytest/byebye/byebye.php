<?php

// Smarty‚ğg‚¦‚é‚æ‚¤‚É‚·‚é
$sma = 'C:\03_shishido\shishido_program_file2.0\Smarty-3.1.18\libs';
set_include_path(get_include_path() . PATH_SEPARATOR . $sma);

require_once('Smarty.class.php');

$smarty = new Smarty();

# Smarty—p‚Ì’Ç‰Á
$smarty->template_dir = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\smartytest\byebye\template';
$smarty->compile_dir  = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\smarty_wk\template_c/';
$smarty->config_dir   = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\smarty_wk\config/';

$smarty->assign('msg','‚Ü‚¶‚Å‚¨‚±‚Á‚½‚Æ‚«‚Ù‚Ç‚·‚ª‚¨‚ª‚¢‚Æ‚µ‚­‚Ä');
$smarty->display('byebye.tpl');