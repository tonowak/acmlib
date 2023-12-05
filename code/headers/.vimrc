set nu rnu hls is ts=4 sw=4
filetype indent on
syntax on
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
\| md5sum \| cut -c-6
