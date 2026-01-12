
# 1. Serial Numbering Scheme

## Function

### System *
- `FC` → flight control
- `PAN` → panel
- `FRA` → frame

---

### Sub-System *
- `FC` flight control → `STK` stick
- `FC` flight control → `PDL` pedal
- `FC` flight control → `COL` collective
- `FC` flight control → `THR` throttle
- `PAN` panel → `FNT` front panel
- `PAN` panel → `PED` pedestal
- `FRA` frame → `SEA` seat
- `FRA` frame → `FC` flight control
- `FRA` frame → `PAN` panel
- `FRA` frame → `MOT` motion

---

### Part (optional)
- `FC` flight control → `STKCOL` stick collective → `SNS` AS5600 hall effect sensor 2020 mount
- `FC` flight control → `STK` stick → `GIM` gimbal
- `FC` flight control → `STK` stick → `GRP` grip
- `FC` flight control → `STK` stick → `ELV` elevation rocker switch
- `FC` flight control → `STK` stick → `TRG` trigger
- `FC` flight control → `STK` stick → `SUB` radio
- `FC` flight control → `COL` stick → `GOV` governor rocker switch
- `PAN` panel → `FNT` front panel → `GBALT` barometric altimeter guage

---

### Assembly (optional)
- `ASSY` assembly

---

### Aircraft Types *
- `H` helicopter
- `F` fixed wing

---

### Models (optional)
- `O` OH-6A

---

## Semantic Version
<Major>.<Minor>.<Variant>-<Manufacture>

---

### Major – Functional Architecture *
Increment when **fundamental compatibility changes** occur:
- Electrical standards (voltage, protocol)
- Mechanical interfaces (mounting pattern)
- Connector type or pinout changes

**Rule:** Parts with different Major versions are *not interchangeable*.

---

### Minor – Backward-Compatible Improvements *
Increment when improvements are made that **do not break system compatibility**:
- Performance improvements
- Efficiency gains
- Tighter tolerances
- Process improvements that preserve interfaces

**Rule:** Same Major, higher Minor → drop-in replacement.

---

### Variant – Parameterized Differences (optional)
Encodes **allowed variations** that preserve basic functionality but affect usage:
- Materials
- Voltage or power class
- Size or profile

**Rule:** Variants are functionally equivalent but not always application-equivalent.

### Manufacture – Manufacturing processes (optional)
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
