%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fsresume.sty (FS専攻合同輪講 TeXフォーマット)                 %
%                                                               %
% Ver 1.0  by 2007年度 教務委員 14/May, 2007                    %
%             多田研究室のスタイルを削って，両面印刷にフィット  %
%             するよう修正, 節の上下空白修正                    %
% Ver 1.1  by 2015年度 教務委員 24/April, 2015                  %
%             エンコードをUTF8に変更　　　　　　　　　　　　　  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%jarticle.sty をインポート
\input{jarticle.sty}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	タイトルを作成する。
%	日付の位置は
%		\dateposition{\flushright}
%	によって右詰めとなる(デフォルトはセンタリング)。
%
\newlength{\@titlespace}	% タイトルの大きさを保持
\setlength{\@titlespace}{5cm}	% デフォルト
\def\titlespace#1{\setlength{\@titlespace}{#1}}	% デフォルトの変更
\def\@dateposition{\center}
\def\dateposition#1{\renewcommand{\@dateposition}{#1}}
%\def\eventname#1{\renewcommand{\@eventname}{#1}}
%\def\origin#1{\def\@origin{#1}}
\def\mylab#1{\def\@mylab{#1}}
\def\mydata#1{\def\@mydata{#1}}
\def\myteacher#1{\def\@myteacher{#1}}
\def\rinkou{
% \def\@eventname{情報システム基盤学専攻合同輪講発表資料}
 \def\@eventname{情報システム基盤学専攻中間発表資料} % 正式名称
 \renewcommand\@maketitle{\newpage
  %\null
  \twocolumn[%
  \vbox to\@titlespace{\hrule\vfill
  \@dateposition{\@date \ \@eventname} \vskip .5em
  \begin{center}
  {\Large \@title \par} \vskip .5em 
  \begin{tabular}{rc}
   所属： & \@mylab \cr
   発表者： & \@mydata \cr
   指導教員： & \@myteacher \cr
  \end{tabular}
  \end{center}
  \vfill\hrule}
  \vskip 1em ]}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 	２段組の各パラメータ値の設定。
%\twocolumn
\@twosidetrue
\@twocolumntrue
\sloppy
\flushbottom
\parindent 1em
\oddsidemargin -4mm
\evensidemargin -12mm
\marginparwidth 10cm 
\marginparsep 10pt 
\textwidth 175mm
\linewidth 175mm
\textheight 265mm
\topmargin -2.3cm
\headheight 0pt
\footskip 10mm
\hbadness=1000
\tolerance=5000 %(Must be less than 10000=sloppy in Japanese)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	section の上下の空白
\renewcommand{\section}{\@startsection{section}{1}{\z@}%
   {.5\Cvs \@plus.3\Cvs}%
   {.5\Cvs \@plus.3\Cvs}%
   {\reset@font\Large\bfseries}}
\renewcommand{\subsection}{\@startsection{subsection}{2}{\z@}%
   {.5\Cvs \@plus.3\Cvs}%
   {.5\Cvs \@plus.3\Cvs}%
   {\reset@font\large\bfseries}}
\renewcommand{\subsubsection}{\@startsection{subsubsection}{3}{\z@}%
   {.5\Cvs \@plus.3\Cvs}%
   {.5\Cvs \@plus.3\Cvs}%
   {\reset@font\normalsize\bfseries}}
\renewcommand{\paragraph}{\@startsection{paragraph}{4}{\z@}%
   {-1em}%
   {-1em}%
   {\reset@font\normalsize\bfseries}}
\renewcommand{\subparagraph}{\@startsection{subparagraph}{5}{\z@}%
   {-1em}%
   {-1em}%
   {\reset@font\normalsize\bfseries}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
