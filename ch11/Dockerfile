FROM alpine:latest
RUN apk update && \
  apk add --no-cache  \
  bash figlet && \
  rm -rf /var/cache/apk/*
CMD ["figlet", "Mysil Rocks!"]
