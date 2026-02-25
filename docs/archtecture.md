# Architecture

## Components

- Agent (C++)
- Backend API (HTTP)
- Frontend (React)

All components run locally.

## Data Flow

Agent -> Backend -> Frontend

- Agent collects system metrics.
- Backend exposes metrics via HTTP/JSON.
- Frontend polls Backend and renders UI.

## Agent

Responsibilities:
- Collect CPU / memory / disk metrics
- OS-specific code isolated (Linux / Windows)

Constraints:
- No networking
- No UI
- No persistence

## Backend

Responsibilities:
- Run HTTP server
- Query Agent
- Return JSON

Notes:
- Agent and Backend may run in the same process (MVP)

## Frontend

Responsibilities:
- Fetch metrics
- Display dashboard

## Out of Scope (MVP)

- Auth
- Remote access
- Alerts
- Multi-host support