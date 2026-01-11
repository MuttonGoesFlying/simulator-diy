
# 1. Serial Numbering Scheme

## Function

### System
- `FC` → flight control
- `PAN` → panel
- `FRA` → frame
- `SEA` → seat
- `MOT` → motion
- `HAP` → haptic

---

### Sub-System
- flight control → `FRAM` flight control frame
- flight control → `STK` stick
- flight control → `PDL` pedal
- flight control → `COL` collective
- flight control → `THR` throttle
- seat → `FRAM` seat frame
- panel → `FNT` front panel
- panel → `PED` pedestal
- motion → `FRAM` seat frame
- haptic → `AUD` audio transducer

---

### Part
- `ASSY` assembly
- front panel → `GBALT` barometric altimeter guage

---

### Aircraft Types
- `H` helicopter
- `F` fixed wing

---

### Models
- `O` OH-6A

---

## Semantic Version
<Major>.<Minor>.<Variant>-<Manufacture>

---

### Major – Functional Architecture
Increment when **fundamental compatibility changes** occur:
- Electrical standards (voltage, protocol)
- Mechanical interfaces (mounting pattern)
- Connector type or pinout changes

**Rule:** Parts with different Major versions are *not interchangeable*.

---

### Minor – Backward-Compatible Improvements
Increment when improvements are made that **do not break system compatibility**:
- Performance improvements
- Efficiency gains
- Tighter tolerances
- Process improvements that preserve interfaces

**Rule:** Same Major, higher Minor → drop-in replacement.

---

### Variant – Parameterized Differences
Encodes **allowed variations** that preserve basic functionality but affect usage:
- Materials
- Voltage or power class
- Size or profile

**Rule:** Variants are functionally equivalent but not always application-equivalent.

### Manufacture – Manufacturing processes
Required manufacturing processes:
- `-3DP` → 3D print (PLA)
- `-DR` → drill
- `-CTSM` → cut soft metal (aluminium, copper)
- `-CTHM` → cut hard metal (steel)
- `-CTSR` → cut chromed steel rod
- `-LZWP` → laser cut & engrave (wood, plastic)
- `-SLD` → solder (basic)
- `-WIR` → wiring
- `-UPL` →  upload software

---

# 2. Metadata Tags (Machine-Readable)

Version numbers alone are not enough. Each hardware release should include a structured metadata:

```yaml
serial: FC-STK-ASSY-H-A-1-0-0 // ASSY should aggregate subcomponent details
interface: I2C
voltage: 24-48V
mounting:
  holes: M3
  spacing: 20mm
manufacturing:
  part:
  process: cut chromed steel rod
  basic_tools: hacksaw with bimetal blade
  intermediate_tools: angle grinder
  advanced_tools:
  materials: 10mm Stainless Steel Chromed Round Bar

  part:
  process: cut hard metal
  basic_tools: hacksaw
  intermediate_tools: angle grinder
  advanced_tools:
  materials: 20mm Stainless Steel Chromed Round Bar
environment:
  temp_range: -20..85C
