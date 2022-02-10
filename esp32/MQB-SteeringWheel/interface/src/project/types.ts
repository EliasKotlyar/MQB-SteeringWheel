export interface LightState {
  led_on: boolean;
}

export interface LightMqttSettings {
  unique_id: string;
  name: string;
  mqtt_path: string;
}

export interface MQBState {
  lastKeyPressed: string;
}

export interface ShiftRegState {
  pin: number;
}

export interface ConfigData {
  mapping: object
}