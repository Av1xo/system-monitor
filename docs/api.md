# API

Base URL:
http://localhost:8080

All responses are JSON.

## GET /api/v1/health

Response:
```json
{
  "status": "ok"
}
```

## GET /api/v1/metrics

Response:
```json
{
  "timestamp": 1700000000,
  "cpu": {
    "usage_percent": 23.4,
    "cores": 8
  },
  "memory": {
    "used_mb": 4120,
    "total_mb": 16384
  },
  "disk": {
    "used_gb": 120,
    "total_gb": 512
  }
}
```

## GET /api/v1/info
```json
{
    "version": "0.0.1",
    "platform": "linux",
    "arch": "x84_64"
}
```

## ERRORS
```json
{
    "error": {
        "code": "INTERNAL_ERROR",
        "message": "Failed to collect metrics"
    }
}
```

## Rules
The frontend is expected to poll /api/v1/metrics periodically.
Recommended interval: 2–5 seconds.

- API is read-only
- Fields are not removed within the same version
- Breaking changes require new version (v2)