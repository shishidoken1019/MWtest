<?php

//
ini_set('display_errors', 'on');
error_reporting(E_ALL);
//
//ini_set('display_errors', 'off');

// MWを使えるようにする
$dir = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\MW';
set_include_path(get_include_path() . PATH_SEPARATOR . $dir);

// Smartyを使えるようにする
$sma = 'C:\03_shishido\shishido_program_file2.0\Smarty-3.1.18\libs';
set_include_path(get_include_path() . PATH_SEPARATOR . $sma);

// 基本的なphp.iniの設定各種
require_once('mw_set_ini.inc');

// 基準ディレクトリの設定
$bp = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\SmartyHelloWorld/';

// configファイル名
$config = $bp . 'conf/config.conf';
//
require_once('controller.inc');

//
$co = new controller;
$co->set_base_path($bp);