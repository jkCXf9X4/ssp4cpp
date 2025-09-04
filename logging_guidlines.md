# 📘 Logging Policy 
## 1. Purpose

This policy defines standards for application logging to ensure:

* Effective debugging and troubleshooting.
* Consistent logging practices across services.
* Clear separation of log levels to avoid noise.
* Compliance with data protection requirements.

---

## 2. Log Levels and Usage

### 🔹 **EXT_TRACE** (Extremely Detailed)

* **Purpose:** Extremely fine-grained logs for debugging at the deepest level.
* **When to use:**

  * Logging variable values inside tight loops.
  * Debugging complex algorithms or edge cases.
* **Notes:** Rarely enabled in production; can generate huge volumes.

### 🔹 **TRACE** (Very Detailed)

* **Purpose:** Very fine-grained logs for debugging at the deepest level.
* **When to use:**

  * Tracking program execution step-by-step.
* **Notes:** Rarely enabled in production; can generate huge volumes.

---

### 🔹 **DEBUG**

* **Purpose:** Developer-focused details that help diagnose issues.
* **When to use:**

  * Lifecycle events (e.g., "Starting background job...").
  * Configuration and environment details at startup.
  * Internal state changes and decision points.
* **Notes:** Typically disabled in production unless troubleshooting.

---

### 🔹 **INFO**

* **Purpose:** General high-level application events.
* **When to use:**

  * Application startup and shutdown messages.
  * Successful completion of important tasks (e.g., "User registered successfully").
  * Business-relevant events worth tracking historically.
* **Notes:** Always safe in production, but should not be too verbose.

---

### 🔹 **WARNING**

* **Purpose:** Something unexpected happened, but the application can continue.
* **When to use:**

  * Using deprecated APIs or features.
  * Failed attempts that may retry successfully (e.g., "Connection lost, retrying...").
  * Potential configuration issues that don’t yet break the system.
* **Notes:** Should prompt investigation but not immediate alarms.

---

### 🔹 **ERROR**

* **Purpose:** A failure that affects the current operation but not the entire system.
* **When to use:**

  * Exceptions that prevent a task from completing.
  * Missing resources or services.
  * User-facing errors (e.g., "Payment processing failed").
* **Notes:** Errors usually need follow-up by developers or operators.

---

### 🔹 **FATAL**

* **Purpose:** Severe issues that cause the system (or major parts of it) to stop functioning.
* **When to use:**

  * Application crash, startup failure.
  * Data corruption or unrecoverable state.
  * Security breach detected.
* **Notes:** Should trigger alerts/paging immediately.

---

## 3. Logging Standards

1. **Clarity**: Messages must be concise and explain the event clearly.

   * ✅ Example: `User login failed: invalid password for user_id=1234`
   * ❌ Bad: `Login error`

2. **Context**: Include identifiers for correlation.

   * ID, time, environment.

3. **Format**: Prefer **structured logging** (JSON or key-value pairs) over plain text.

4. **No Sensitive Data**: Never log passwords, tokens or personal information (PII).

5. **Error Handling**: Always log exceptions with stack traces at **DEBUG** or **ERROR** (depending on severity).

6. **Log Rotation & Retention**:

   * No policy

7. **Monitoring**:

   * WARN, ERROR, and FATAL logs should be tracked in monitoring systems.
   * FATAL logs must trigger **alerts** immediately.

---

## 4. Environment Guidelines

* **Development**: EXT_TRACE, TRACE, DEBUG, INFO, WARN, ERROR, FATAL enabled.
* **Production**: INFO, WARN, ERROR, FATAL enabled.

---
