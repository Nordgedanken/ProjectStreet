<?php

require_once("../inc/util.inc");
require_once("../inc/phpmailer/PHPMailerAutoload.php");

$master_url = parse_config(get_config(), "<master_url>");
define("PROJECT", "ProjectStreet@Car");
define("URL_BASE", $master_url);
//define("SECURE_URL_BASE",str_replace("http","https",$master_url));
define("SECURE_URL_BASE", $master_url);
define("IMAGE_PATH", "../user_profile/images/");
define("IMAGE_URL", "user_profile/images/");
define("PROFILE_PATH", "../user_profile/");
define("PROFILE_URL", "user_profile/");
define("LANGUAGE_FILE", "languages.txt");
define("STYLESHEET", "projectstreet.css");
define("FORUM_QA_MERGED_MODE", true);
define("COPYRIGHT_HOLDER", "<a href=\"http://nordgedanken.de\">Marcel Radzio</a>");
define("SYS_ADMIN_EMAIL", "info@nordgedanken.de");
define("UOTD_ADMIN_EMAIL", "info@nordgedanken.de"); # who gets user of the day pool running low e-mails?


// Email addresses separated by pipe ( | ) that will receive user reported
// offensive forum posts.
define("POST_REPORT_EMAILS", "info@nordgedanken.de");

function page_head(
    $title, $java_onload=null, $title_plain=null, $prefix="", $head_extra=null
) {
    global $caching, $cache_control_extra, $did_page_head;

    $did_page_head = true;
    $url_base = url_base();
    $stylesheet = $url_base.STYLESHEET;
    $rssname = PROJECT . " RSS 2.0";
    $rsslink = $url_base."rss_main.php";
    if (defined('STYLESHEET2')) {
        $stylesheet2 = $url_base.STYLESHEET2;
    } else {
        $stylesheet2 = null;
    }


    if (!$caching) {
        header("Content-type: text/html; charset=utf-8");
        header ("Expires: Mon, 26 Jul 1997 05:00:00 UTC");    // Date in the past
        header ("Last-Modified: " . gmdate("D, d M Y H:i:s") . " UTC"); // always modified
        header ("Cache-Control: $cache_control_extra no-cache, must-revalidate, post-check=0, pre-check=0");  // HTTP/1.1
        header ("Pragma: no-cache");                          // HTTP/1.0
    }

    echo "<!DOCTYPE html>";

    echo "<html><head>\n";
    if ($head_extra) {
        echo "\n$head_extra\n";
    }
    if (!$title_plain) {
        echo "<title>".sanitize_tags($title)."</title>\n";
    } else {
        echo "<title>".sanitize_tags($title_plain)."</title>\n";
    }
    echo "
    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">
    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\">
    <link rel=\"stylesheet\" type=\"text/css\" href=\"$stylesheet\">
    <link rel=\"alternate\" type=\"application/rss+xml\" title=\"$rssname\" href=\"$rsslink\">
    <link href='https://fonts.googleapis.com/css?family=Merriweather+Sans' rel='stylesheet' type='text/css'>
    <link href='https://fonts.googleapis.com/css?family=Merriweather+Sans:700' rel='stylesheet' type='text/css'>
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no\">";
    echo <<<END
    <script type="text/javascript" src="drop_down.js"></script>
    <!--[if lte IE 6]>
      <script type="text/javascript" src="supersleight-min.js"></script>
    <![endif]-->

    <script>
  	(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  	(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  	m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  	})(window,document,'script','https://www.google-analytics.com/analytics.js','ga');

  	ga('create', 'UA-85483437-1', 'auto');
  	ga('send', 'pageview');

    </script>

    <script src='https://www.google.com/recaptcha/api.js'></script>
    <script src='https://code.jquery.com/jquery-3.1.1.min.js' integrity='sha256-hVVnYaiADRTO2PzUGmuLJr8BLUSjGIZsDYGmIJLv2b8=' crossorigin='anonymous'></script>
    <script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js' integrity='sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa' crossorigin='anonymous'></script>

  </head>

END;
    if ($java_onload){
        echo "<body onload=\"".$java_onload."\">";
    } else {
        echo "<body>";
    }
    display_cvs_versions();
    project_banner($title, $prefix);
    switch($title) {    //kludge
      case tra("Your account"):
        show_login_info($prefix);
      default:
        break;
    }


}


function project_banner($title, $prefix) {
    // Put your project title and logo here
    $url_base = url_base();
    echo "
	<nav class='navbar navbar-inverse navbar-fixed-top'>
		<div class='container'>
		<!-- Brand and toggle get grouped for better mobile display -->
			<div class='navbar-header'>
				<button type='button' class='navbar-toggle collapsed' data-toggle='collapse' data-target='#bs-example-navbar-collapse-1' aria-expanded='false'>
					<span class='sr-only'>Toggle navigation</span>
					<span class='icon-bar'></span>
					<span class='icon-bar'></span>
					<span class='icon-bar'></span>
				</button>
			</div>
			<div class='collapse navbar-collapse' id='bs-example-navbar-collapse-1'>
				<ul class='nav navbar-nav'>
					<li><a href='/join.php'>JOIN</a></li>
					<li><a href='/faq.php'>FAQ</a></li>
					<li><a href='/forum_index.php'>FORUMS</a></li>
					<li class='dropdown'>
						<a href='#' class='dropdown-toggle' data-toggle='dropdown' role='button' aria-haspopup='true' aria-expanded='false'>COMMUNITY <span class='caret'></span></a>
						<ul class='dropdown-menu'>
							<li><a href='/home.php'>Your Account</a></li>
							<li><a href='/team.php'>Teams</a></li>
							<li><a href='/downloads.php'>Desktop Backgrounds</a></li>
							<li><a href='/profile_menu.php'>Participant Profiles</a></li>
							</ul>
					</li>
					<li class='dropdown'>
						<a href='#' class='dropdown-toggle' data-toggle='dropdown' role='button' aria-haspopup='true' aria-expanded='false'>SERVER <span class='caret'></span></a>
						<ul class='dropdown-menu'>
							<li><a href='/apps.php'>Applications</a></li>
							<li><a href='/server_status.php'>Server Status</a></li>
							<li><a href='https://github.com/Nordgedanken/ProjectStreet'>Development</a></li>
						</ul>
					</li>
					<li class='dropdown'>
						<a href='#' class='dropdown-toggle' data-toggle='dropdown' role='button' aria-haspopup='true' aria-expanded='false'>STATS <span class='caret'></span></a>
						<ul class='dropdown-menu'>
							<li><a href='/top_users.php'>Top Participants</a></li>
							<li><a href='/top_hosts.php'>Top Computers</a></li>
							<li><a href='/top_teams.php'>Top Teams</a></li>
							<li><a href='/stats.php'>Other Statistics</a></li>
						</ul>
					</li>
				</ul>
			</div>
		</div>
	</nav>
	<a href='$url_base'>
		<div class='wide'>
  			<div class='col-xs-5 line'><hr></div>
			<div class='col-xs-2 logo'>ProjectStreet@Car</div>
			<div class='col-xs-5 line'><hr></div>
		</div>
	</a>
	<div class='container-fluid'>
   ";
}

function project_footer($show_return, $show_date) {
    echo "<footer class='footer'>";

    if ($show_return) {
        echo "<a href=".URL_BASE.">Return to ".PROJECT." main page</a>\n";
    }
    echo "<br><br>Copyright &copy; ".date("Y ").COPYRIGHT_HOLDER."<br/>\n";

	echo <<<END
If you have any questions or comments regarding the content of this site, please contact <a href='http://nordgedanken.de'>Marcel Radzio</a><br/>
END;
    if ($show_date) {
        echo "<font size=-2 color=bbbbbb>Generated ",time_str(time()),"</font>\n";
    }
	echo "
	<div id='sponsors'>
		<p>No Sponsors at this time :)</p>
	</div>
	</footer>";
}

function show_profile_heading1() {
    return tra("Your personal background.");
	}

function show_profile_question1() {
    return tra("Tell us about yourself. You could tell us where you're from, your age, occupation, hobbies, or anything else about yourself.");
}

function show_profile_heading2() {
    return tra("Your opinions about %1", PROJECT);
}

function show_profile_question2() {
    return tra("Tell us your thoughts about %1<ol>
    <li>Why do you run %1?
        <li>What are your views about the project?
        <li>Any suggestions?
    </ol>", PROJECT);
}

function project_workunit($wu){
    // shown in the workunit page
}

function project_user_summary($user){
    // shown in the user summary page
}

function project_user_page_private($user){
    // shown in the private account page
}
if (0) {

// show project-specific credit on user/team pages
//
function show_app_credit_user($user, $app_name, $appids) {
    $t = 0;
    $a = 0;
    $n = 0;
    foreach ($appids as $appid) {
        $cu = BoincCreditUser::lookup(
            "userid=$user->id and appid=$appid and credit_type=0"
        );
        if ($cu) {
            $t += $cu->total;
            $a += $cu->expavg;
            $n += $cu->njobs;
        }
    }
    row2("$app_name credit",
        format_credit_large($t)." total, ".
        format_credit($a)." average".
        " ($n tasks)"
    );
}
function show_app_credit_team($team, $app_name, $appids) {
    $t = 0;
    $a = 0;
    $n = 0;
    foreach ($appids as $appid) {
        $ct = BoincCreditTeam::lookup(
            "teamid=$team->id and appid=$appid and credit_type=0"
        );
        if ($ct) {
            $t += $ct->total;
            $a += $ct->expavg;
            $n += $ct->njobs;
        }
    }
    row2("$app_name credit",
        format_credit_large($t)." total, ".
        format_credit($a)." average".
        " ($n tasks)"
    );
}

// a list of "sub-projects", used in the display of per-app credit and badges.
// A subproject is:
// - a set of 1 or more apps; an app can belong to at most 1 subproject.
// - a name, shown on the web site
// - a short name, used in badge names.  Don't use "total".
//
$sub_projects = array(
    array("name" => "Remote Test", "short_name" => "RT", "appids" => array(16)),
    array("name" => "Uppercase", "short_name" => "UC", "appids" => array(1, 25)),
);

function project_user_credit($user){
    global $sub_projects;
    foreach ($sub_projects as $sp) {
        show_app_credit_user($user, $sp["name"], $sp["appids"]);
    }
}

function project_team_credit($team) {
    global $sub_projects;
    foreach ($sub_projects as $sp) {
        show_app_credit_team($team, $sp["name"], $sp["appids"]);
    }
}

}   // if(0)

function project_forum_post_rules() {
    // additional forum post rules
    return "";
}


function make_php_mailer() {

    $mail = new PHPMailer();
    $mail->IsSMTP();
    $mail->SMTPAuth = false;
    $mail->SMTPSecure = "";
    $mail->Host = "";
    $mail->Port = 25;
    $mail->Username = "";
    $mail->Password = "";
    $mail->SetFrom('info@nordgedanken.de', 'ProjectStreetAtCar');
    $mail->AddReplyTo("info@nordgedanken.de", "ProjectStreetAtCar");

    $mail->SMTPOptions = array(
        'ssl' => array(
            'verify_peer' => false,
            'verify_peer_name' => false,
            'allow_self_signed' => true
        )
    );

    return $mail;
}

function server_status_project_info(){

  list($short,$date) = explode(',',file_get_contents(project_dir()."/.gittag"));
  echo "Server version: <a href='https://github.com/Nordgedanken/ProjectStreet/commits/$short'>$short</a> ($date UTC)";

}

?>
